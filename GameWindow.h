#include <QString>

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

class GameWindow
{
private:
    QString intro
        = "<center>"
          "<h1>Toast!</h1>"
          "<p>A Zork inspired text-adventure game with GUI controls.</p></center><hr/><br/>"
          "<p>While making your toast this morning, you have been shrunk down and trapped inside "
          "the "
          "toaster.<br/>Escape before your toast pops or you're toast!<br/>"
          "<i>by Adam Byrne</i>"
          "<br/><br/><h4>Type <u>start</u> to embark on your adventure.</h4>"
          "</p>";

    friend class MainWindow;
};
#endif // GAMEWINDOW_H
