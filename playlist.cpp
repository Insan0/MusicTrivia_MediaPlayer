#include "playlist.h"

Playlist::Playlist(QString name)
{
    this->name = name;
    n = 0;
}


QString Playlist::getName() { return name; }
void Playlist::setName(QString name) { this->name = name; }


bool Playlist::getChanged(){ return changed; }
void Playlist::setChanged(bool changed){ this->changed = changed; }


void Playlist::add(Song s)
{
    list[n] = s;
    n++;
}


void Playlist::remove(int j)
{
    n--;
    for (int i = j; i < n; i++)
    {
        list[i] = list[i+1];
    }
}


void Playlist::save()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Save Playlist", "", "Playlist (*.plt)");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Failed to save");
        return;
    }

    QTextStream out(&file);
    out << n << Qt::endl << name << Qt::endl;
    for(int i = 0; i < n; i++)
    {
        out << list[i];
    }
    file.flush();
    file.close();
}


void Playlist::load(QFile &file)
{
    QTextStream in(&file);

    in >> n;
    in.readLine();
    name = in.readLine();

    for(int i = 0; i < n; i++)
    {
        in >> list[i];
        in.readLine();
    }
}
