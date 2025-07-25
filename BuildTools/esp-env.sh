#!/usr/bin/env bash

echo -e "\033[1;36m🚀 Iniciando entorno personalizado ESP8266 RTOS SDK...\033[0m"

# 📁 Ruta base al SDK y Forks
SDK_PATH="/c/esp/ESP8266_RTOS_SDK"
MBEDTLS_PATH="/c/esp/ESP8266_RTOS_SDK/components/mbedtls/mbedtls"
GIT_PATH="/c/Tools/Git/bin"
VENV_PATH="$HOME/.espressif/python_env/rtos3.4_py3.13_env"
ACTIVATE_PATH="$VENV_PATH/Scripts/activate"
KCONF_PATH="/c/esp/tools/kconfig"

# 🧰 Añadir Git y mconf-idf al PATH si no están
for path in "$GIT_PATH" "$KCONF_PATH"; do
  if [[ ":$PATH:" != *":$path:"* ]]; then
    export PATH="$PATH:$path"
  fi
done

# 🔍 Validar que existan componentes clave
declare -A REQUIRED_PATHS=(
  ["mbedtls"]="CMakeLists.txt"
  ["cJSON"]="components/json/cJSON/cJSON.c"
  ["mqtt"]="components/mqtt/esp-mqtt/mqtt_client.c"
  ["lwip"]="components/lwip/lwip/src/api/api_lib.c"
)

for name in "${!REQUIRED_PATHS[@]}"; do
  CHECK="$SDK_PATH/${REQUIRED_PATHS[$name]}"
  if [[ ! -f "$CHECK" ]]; then
    echo -e "\033[1;31m⚠️ Submódulo '$name' incompleto o roto → $CHECK\033[0m"
  else
    echo -e "\033[1;32m✅ Submódulo '$name' listo\033[0m"
  fi
done

# 🛠️ Ejecutar install.sh para preparar herramientas y entorno Python
if [[ -f "$SDK_PATH/install.sh" ]]; then
  echo -e "\033[1;33m⚙️ Ejecutando install.sh...\033[0m"
  source "$SDK_PATH/install.sh"
else
  echo -e "\033[1;31m🚫 install.sh no encontrado en: $SDK_PATH\033[0m"
fi

# 🧠 Exportar variables de entorno del SDK
if [[ -f "$SDK_PATH/export.sh" ]]; then
  echo -e "\033[1;33m📦 Ejecutando export.sh...\033[0m"
  source "$SDK_PATH/export.sh"
else
  echo -e "\033[1;31m🚫 export.sh no encontrado en: $SDK_PATH\033[0m"
fi

# 🐍 Activar entorno virtual generado por el SDK
if [[ -f "$ACTIVATE_PATH" ]]; then
  source "$ACTIVATE_PATH"
  echo -e "\033[1;32m✅ Entorno virtual activado: $VENV_PATH\033[0m"
else
  echo -e "\033[1;31m🚫 Entorno virtual no encontrado en: $VENV_PATH\033[0m"
fi

# 🔍 Verificar disponibilidad de idf.py
if command -v idf.py >/dev/null 2>&1; then
  echo -e "\033[1;32m✅ idf.py disponible en el entorno\033[0m"
else
  echo -e "\033[1;31m❌ idf.py no está en el PATH. Revisa export.sh y entorno virtual\033[0m"
fi