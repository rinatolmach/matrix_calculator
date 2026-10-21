
# Этап 1. Сборка программы
FROM ubuntu:22.04 AS builder

# Установка инструментов компиляции
RUN apt-get update && \
    apt-get install -y \
        cmake \
        g++ \
        libgtest-dev && \
    rm -rf /var/lib/apt/lists/*

# Рабочая папка внутри контейнера
WORKDIR /app

# Копирование исходного кода
COPY . .

# Настройка и сборка проекта
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --parallel 2

# Этап 2. Запуск готовой программы
FROM ubuntu:22.04

# Рабочая папка
WORKDIR /app

# Копирование исполняемого файла
COPY --from=builder /app/build/matrix_calculator .

# Копирование файла с матрицей
COPY --from=builder /app/matrix.txt .

# Команда запуска приложения
CMD ["./matrix_calculator"]
