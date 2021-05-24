# Emovie
Программа для распознования эмоций на протяжении фильма. Запишите себя на видео, пока смотрите фильм, и посмотрите, какие эмоции вы испытвали.


# Установка
Необходимая версия python: 3.6.6 (версии выше не поддерживают tensorflow требуемой версии).

Необходимые библиотеки для python:
- numpy==1.17.4
- opencv-python==4.1.2.30
- tensorflow==2.1.3

В файле emodetection.cpp замените пути к виртуальному окружению и файлу emotions.py на свои (пути должны быть абсолютными).

Вам понадобится собрать программу самостоятельно с помощью qmake.

# Тестирование
В корне лежит видео video.mp4. Запустив программу, вы можете выбрать его в качестве семпла.
