#include "arbo.h"

void Arbo::insertFather(QString name){
    item = new QStandardItem(name);
    item->setEditable(false);
}

void Arbo::insertChildren(QString name) {
    QStandardItem *subItem = new QStandardItem(name);
    subItem->setCheckable(true);
    subItem->setEditable(false);
    item->appendRow(subItem);
}

void Arbo::setItem(QStandardItemModel *model) {
    model->setItem(nRow, item);
    nRow++;
}

void Arbo::preOrder(QDomNode dom, QStandardItemModel *model) {
    cout << "Coucou" << endl;
    if (!dom.isNull()) {
        string aux = dom.nodeName().toStdString();
        string name = "name";
        string value = "value";
        if(dom.isText()){
            cout << "ICI";
            aux = dom.parentNode().nodeName().toStdString();
            if (strcmp(aux.c_str(),name.c_str()) == 0) {
                cout << dom.nodeValue().toStdString() << endl;
                insertFather(dom.nodeValue());
                setItem(model);
            }
            if (strcmp(aux.c_str(),value.c_str()) == 0) {
                cout << "\t" << dom.nodeValue().toStdString() << endl;
                insertChildren(dom.nodeValue());
            }
        } else {
            preOrder(dom.firstChild(), model);
            preOrder(dom.nextSibling(), model);
        }

    } else {
        cout << "Dom is null" << endl;
    }
}

Arbo::Arbo()
{
    cout << "Hello" << endl;
    setFixedSize(300, 500);

    QVBoxLayout *layout = new QVBoxLayout;

    //QFile file("test.xml");
   /* char s[256];
    file.readLine(s, 256);*/

    QFile file2("out2.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))
       return;


    QDomDocument doc("mydocument");
        QFile file("out2.txt");
        if (!file.open(QIODevice::ReadOnly)){
            cout<< "ERROR 1"<< endl;
            return;
        }
        if (!doc.setContent(&file)) {
            cout << "ERROR 2" << endl;
            file.close();
            return;
        }
        file.close();




    doc.setContent(&file);

    QStandardItemModel *model = new QStandardItemModel();
    this->preOrder(doc.firstChild(), model);

    QDirModel *modele = new QDirModel;
    QTreeView *vue = new QTreeView;
    vue->setModel(model);
    vue->show();

    layout->addWidget(vue);
    this->setLayout(layout);

}
