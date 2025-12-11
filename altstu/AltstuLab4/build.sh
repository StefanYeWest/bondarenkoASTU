#!/bin/bash
# Скрипт для сборки и запуска проекта C#

DOTNET_PATH="/usr/local/share/dotnet/dotnet"

if [ ! -f "$DOTNET_PATH" ]; then
    echo "Ошибка: dotnet не найден по пути $DOTNET_PATH"
    echo "Попробуйте использовать: dotnet build"
    exit 1
fi

cd "$(dirname "$0")"

echo "=== Сборка проекта ==="
$DOTNET_PATH build

if [ $? -eq 0 ]; then
    echo ""
    echo "=== Запуск программы ==="
    $DOTNET_PATH run
else
    echo "Ошибка сборки!"
    exit 1
fi




