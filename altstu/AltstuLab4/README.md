# Лабораторная №4 (C#)

## Структура
- `AltstuLab4.csproj` — консольное приложение .NET 8
- `Program.cs` — демонстрация сценариев (статические/динамические объекты, ссылки, массивы)
- `Domain/` — портированные классы из лабораторной №3

## Предварительные требования
1. Установить **.NET SDK 8+** с [official .NET](https://dotnet.microsoft.com/ru-ru/download) или через пакетный менеджер (`brew install dotnet`).
2. Проверить установку: `dotnet --version`.

**Примечание для macOS:** Если `dotnet` не найден в PATH, используйте полный путь: `/usr/local/share/dotnet/dotnet` или добавьте в PATH:
```bash
export PATH="/usr/local/share/dotnet:$PATH"
```

## Сборка и запуск (macOS/Linux/Windows)
```bash
cd AltstuLab4
dotnet build
dotnet run
```

**Если dotnet не в PATH:**
```bash
/usr/local/share/dotnet/dotnet build
/usr/local/share/dotnet/dotnet run
```

## Публикация
- Сборка в `.dll` (portable):
  ```bash
  dotnet publish -c Release -o publish
  ```
- Сборка в `.exe` для Windows:
  ```bash
  dotnet publish -c Release -r win-x64 -p:PublishSingleFile=true --self-contained true -o publish-win
  ```

## Демонстрация на двух платформах
1. Сборка на macOS → запуск `dotnet run`.
2. Скопировать папку `publish-win` на Windows ПК → запустить `AltstuLab4.exe`.

## Pull Request
1. Создать ветку `lab4-csharp`.
2. `git add AltstuLab4`
3. `git commit -m "Add C# console app for lab 4"`
4. `git push origin lab4-csharp`
5. Открыть PR, назначить преподователя в Reviewer и Assignee.

