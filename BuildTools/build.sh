#!/bin/bash

# Log file to store the output of the script
# The log file will be named with the current date and time
LOGFILE="build.ansi"

# Redirige stdout y stderr a tee, que escribe en pantalla y en el log
exec > >(tee -a "$LOGFILE") 2> >(tee -a "$LOGFILE" >&2)

# This script sets up the environment for building projects with the ESP8266 RTOS SDK.
SDK_NAME="ESP8266_RTOS_SDK"
SDK_VERSION="3.4.0"

# Define the SDK directories
SDK_ROOT_DIR="$HOME/esp/$SDK_NAME"
SDK_VENV_DIR="$SDK_ROOT_DIR/.venv"
SDK_VENV_BIN_DIR="$SDK_VENV_DIR/bin"
SDK_VENV_ACTIVATE="$SDK_VENV_BIN_DIR/activate"

# Define project directories
PROJECT_ROOT_DIR="$(dirname $(pwd))"
PROJECT_SOURCE_DIR="$PROJECT_ROOT_DIR/Source"
PROJECT_TARGET_DIR="$PROJECT_ROOT_DIR/Target"
PROJECT_BUILDTOOLS_DIR="$PROJECT_ROOT_DIR/BuildTools"
PROJECT_PACKAGE_FILE="$PROJECT_BUILDTOOLS_DIR/package.yaml"

# Variable to track if an error occurred during the build process
error_count=0

# Function to check if a flag is present in the arguments
has_flag() {
    local flag="$1"
    for arg in "$@"; do
        if [ "$arg" = "$flag" ]; then
            return 0  # true
        fi
    done
    return 1  # false
}

# Function to validate the existence of directories
validate_directory() {
    if [ -d "$1" ]; then
        echo -e "\e[34m📁 $2: $1\e[0m"
    else 
        echo -e "\e[31m❌ Error: $2 directory $1 does not exist.\e[0m"
        exit 1
    fi
}

# Function to validate the existence of files
validate_file() {
    if [ -f "$1" ]; then
        echo -e "\e[34m📄 $2: $1\e[0m"
    else 
        echo -e "\e[31m❌ Error: $2 file $1 does not exist.\e[0m"
        exit 1
    fi
}

# Function to activate the virtual environment
activate_venv() {
    if [ -f "$1" ]; then
        source "$1"
        echo -e "\e[1m▶️  $2 virtual environment activated.\e[0m"
    else
        echo -e "\e[1m❌ Error: activate script not found in $(dirname $1)\e[0m"
        exit 1
    fi
}

# Function to deactivate the virtual environment
deactivate_venv() {
    if [ -n "$1" ]; then
        deactivate
        echo -e "\e[1m⏹️  $2 virtual environment deactivated.\e[0m"
    else
        echo -e "\e[1m❌ Error: No virtual environment is currently active.\e[0m"
    fi
}   

# Function to change to a specified directory
move_to_directory() {
    if [ -d "$1" ]; then
        cd "$1"
        echo -e "\e[33m Changed to directory: $1\e[0m"
    else
        echo -e "\e[1m❌ Error: Directory $1 does not exist.\e[0m"
        exit 1
    fi
}

# Function to validate the clean process
validate_clean() {
    if [ $? -ne 0 ]; then
        echo -e "\e[1m❌ Error: Failed to clean the project.\e[0m"
        error_count=$((error_count + 1))
    fi
    echo -e "\e[1m✅ Project cleaned successfully.\e[0m"
}

# Function to validate the build and flash process
validate_build_flash() {
    if [ $? -ne 0 ]; then
        echo -e "\e[1m❌ Error: Failed to build and flash the project.\e[0m"
        error_count=$((error_count + 1))
    fi
    echo -e "\e[1m✅ Project built and flashed successfully.\e[0m"}
}

# Function to process the package.yaml file
process_package_yaml() {
    package_completed=true
    # Read the structure from the package.yaml file
    num_rules=$(yq '.structure | length' "$PROJECT_PACKAGE_FILE")
    for i in $(seq 0 $((num_rules - 1))); do
        name=$(yq ".structure[$i].name" "$PROJECT_PACKAGE_FILE" | sed 's/^"\(.*\)"$/\1/')
        match=$(yq ".structure[$i].match" "$PROJECT_PACKAGE_FILE" | sed 's/^"\(.*\)"$/\1/')
        origin=$(yq ".structure[$i].origin" "$PROJECT_PACKAGE_FILE" | sed 's/^"\(.*\)"$/\1/')
        dest=$(yq ".structure[$i].destination" "$PROJECT_PACKAGE_FILE" | sed 's/^"\(.*\)"$/\1/')
        mkdir -p "$PROJECT_ROOT_DIR/$dest"
        echo "📦 Copying files to '$dest':"
        # Split the match patterns by '|'
        IFS='|' read -ra patterns <<< "$match"
        # Initialize an array to hold all matched files      
        all_files=()
        for pattern in "${patterns[@]}"; do
            mapfile -t matched < <(find "$PROJECT_ROOT_DIR/$origin" -type f -name "$pattern")
            all_files+=("${matched[@]}")
        done
        # Check if any files were found
        if [ "${#all_files[@]}" -gt 0 ]; then
            for i in "${!all_files[@]}"; do
                file="${all_files[$i]}"
                cp "$file" "$PROJECT_ROOT_DIR/$dest/"
                
                if [ "$i" -eq $((${#all_files[@]} - 1)) ]; then
                    echo " └── $file"
                else
                    echo " ├── $file"
                fi
            done
        else
            echo " ⚠️  No files found matching any pattern."
            package_completed=false
        fi

    done
    # Check if all files were copied
    if [ "$package_completed" = false ]; then
        echo "❌ Error: Some files were not found or copied."
        error_count=$((error_count + 1))
    else
        echo "✅ All files processed successfully."
    fi
}

# Function to compress the release directory
compress_release() {
    local archive_name="$PROJECT_TARGET_DIR/release.7z"
    local source_dir="$PROJECT_TARGET_DIR/release"

    if [ -d "$source_dir" ]; then
        echo -e "\e[1;34m📦 Compressing '$source_dir' into '$archive_name'...\e[0m"
        7z a "$archive_name" "$source_dir" > /dev/null
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32m✅ Compression successful: $archive_name\e[0m"
        else
            echo -e "\e[1;31m❌ Compression failed.\e[0m"
            exit 1
        fi
    else
        echo -e "\e[1;31m❌ Error: Directory '$source_dir' does not exist.\e[0m"
        exit 1
    fi
}

# Function to clean the project
make_clean() {
    # Change to the project source directory
    echo "Changing to project source directory..."
    move_to_directory "$PROJECT_SOURCE_DIR"
    echo
    # Clean the project
    echo "Cleaning project..."
    make clean
    validate_clean
    echo
    # Return to the original directory
    echo "Returning to project root directory: $PROJECT_ROOT_DIR"
    move_to_directory "$PROJECT_ROOT_DIR"
    echo 
}

# Function to build and flash the project
make_flash() {
    # Change to the project source directory
    echo "Changing to project source directory..."
    move_to_directory "$PROJECT_SOURCE_DIR"
    echo
    # Build & Flash project
    echo "Building & flashing project..."
    make flash -j $(nproc)
    validate_build_flash
    echo
    # Return to the original directory
    echo "Returning to project root directory: $PROJECT_ROOT_DIR"
    move_to_directory "$PROJECT_ROOT_DIR"
    echo 
}

# Function to create the package
make_package() {
    # Create package structure
    echo "Processing package.yaml file: $PROJECT_PACKAGE_FILE"
    process_package_yaml
    echo
    compress_release
    echo
}

# Function to perform all build steps
make_all() {
    make_clean
    make_flash
    make_package
}

# Validate SDK directories
echo "Validating $SDK_NAME $SDK_VERSION directories..."
validate_directory "$SDK_ROOT_DIR" "SDK root"
validate_directory "$SDK_VENV_DIR" "SDK virtual environment"
validate_directory "$SDK_VENV_BIN_DIR" "SDK virtual environment bin"
echo

# Validate project directories
echo "Validating project directories..."
validate_directory "$PROJECT_ROOT_DIR" "Project Root"
validate_directory "$PROJECT_SOURCE_DIR" "Project Source"
validate_directory "$PROJECT_BUILDTOOLS_DIR" "Project BuildTools"
echo 

# Validate the package.yaml file (conditional)
if has_flag "package" "$@"; then
    echo "Validating package.yaml file..."
    validate_file "$PROJECT_PACKAGE_FILE" "Package YAML file"
    echo 
fi

# Activate the SDK virtual environment
echo "Activating $SDK_NAME $SDK_VERSION virtual environment..."
activate_venv "$SDK_VENV_ACTIVATE" "$SDK_NAME $SDK_VERSION"
echo 

# Process multiple user input flags
for arg in "$@"; do
    case "$arg" in
        clean)
            make_clean
            ;;
        flash)
            make_flash
            ;;
        package)
            make_package
            ;;
        all)
            make_all
            break
            ;;
        *)
            echo "❌ Error: Unknown option '$arg'"
            echo "Usage: $0 {clean|flash|package|all} [additional flags...]"
            error_count=$((error_count + 1))
            echo
            ;;
    esac
done

# deactivate the virtual environment
echo "Deactivating $SDK_NAME $SDK_VERSION virtual environment..."
deactivate_venv "$SDK_VENV_ACTIVATE" "$SDK_NAME $SDK_VERSION"
echo

if [ $error_count -ne 0 ]; then
    echo -e "❌ Build process finished with \e[31m\e[4m$error_count errors.\e[0m"
    exit 1
else
    echo -e "\e[32m✅ Build process completed successfully.\e[0m"
fi