# Как запустить

#### *1. Необходимо установить:*
  * Qt 5.4.2 ([Скачать Qt Online Installer](http://download.qt.io/archive/online_installers/1.6/qt-opensource-windows-x86-1.6.0-8-online.exe "Download Qt"))
    - В установщике, помимо Qt 5.4.2, выбрать MinGW 4.9.1 и Source Components
  * OpenCV 2.4.12 ([Скачать можно тут](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.12/opencv-2.4.12.exe/download "Download OpenCV"))
  * CMake 3.5.1 ([Скачать CMake Windows Installer](https://cmake.org/files/v3.5/cmake-3.5.1-win32-x86.msi "Download CMake")) 
  
#### *2. Cвязываем OpenCV c Qt:* 
  Для удобства отмечу: *dir_qt* является каталогом, в который был установлен Qt, *dir_opencv* - каталогом, куда был распакован OpenCV 
  
  * В переменную окружения **PATH** добавить *dir_qt\5.4\\mingw491_32\bin;dir_qt\Tools\mingw491_32\bin;*
  * Запускаем *cmake-gui.exe* (находится в каталоге bin установки CMake)
    - в **Where is the source code:** выбираем каталог *dir_opencv\sources*
    - в **Where to build the binaries:** выбираем каталог *dir_opencv\build*
    - жмём на **Configure**
    - в появившемся окне нажимаем на **Yes**
    - в раскрывающемся списке выбираем **MinGW Makefiles**, выбираем **Specify native compiler** и жмём **Next**
    - далее для С выбираем компилятор *dir_qt\Tools\mingw491_32\bin\gcc.exe*
    - для С++ - *dir_qt\Tools\mingw491_32\bin\g++.exe*
    - жмём **Finish**
    - ставим галочку напротив **WITH_QT** и жмём ещё раз на **Configure**
    - для **CMAKE_BUILD_TYPE** выбираем Debug и ещё раз жмём на **Configure**
    - после появления **Configuring done** жмём на **Generate**
    - после появления **Generating done** закрываем CMake
  * Открываем CMD
    - переходим в каталог с бинарниками `cd dir_opencv\build`
    - выполняем `mingw32-make -j2`
    - после успешного завершения устанавливаем библиотеки `mingw32-make install -j2`
  * После установки библиотек необходимо в переменную окружения **PATH** добавить *dir_opencv\build\include;dir_opencv\build\bin;*
  * Если требуется, в файле logo_recognition.pro изменить **INCLUDEPATH** и **LIBS** *на dir_opencv/build/install/include*
  
#### *3. Сборка*
  * Открыть проект в QtCreator
  * Нажмаем на `Ctrl+Shift+B`
  * После успешной сборки нажимаем на `Ctrl+R`
  * Для release сборки в панели слева необходимо выбрать **Выпуск**
  * Если требуется статическая сборка, можно воспользоваться [данной инструкцией](http://www.cyberforum.ru/blogs/416874/blog2924.html)

# Описание программы
![Alt-текст](http://www.picshare.ru/uploads/160406/m4DBIy55D5.png)

  1 - кнопка для выбора каталога, в котором хранятся изображения логотипов   
  2 - после выбора каталога с логотипами, здесь отобразится путь выбранного каталога   
  3 - кнопка для выбора каталога, в котором хранятся ихображения, на которых будут распознаваться указанные логотипы   
  4 - после выбора каталога с изорбражениями, здесь отобразиться путь выбранного каталога   
  5 - кнопка, запускающая процесс распознования логотипов
  
# Результаты программы на одном из наборов данных
  [Посмотреть результат]()
