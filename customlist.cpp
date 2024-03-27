#include "customList.h"

CustomList::CustomList(QWidget *parent) : QListWidget(parent) {
    // Vous pouvez initialiser des paramètres spécifiques au widget ici si nécessaire
}

void CustomList::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        QListWidgetItem *currentItem = this->currentItem();
        int currentIndex = this->row(currentItem);

        // Déterminez la direction en fonction de la touche pressée
        int step = (event->key() == Qt::Key_Up) ? -1 : 1;

        // Tentez de sélectionner le prochain élément non désactivé
        for (int i = currentIndex + step; i >= 0 && i < this->count(); i += step) {
            QListWidgetItem *nextItem = this->item(i);
            if ((nextItem->flags() & Qt::ItemIsEnabled)) {
                // Sélectionnez l'élément suivant qui est activé
                this->setCurrentItem(nextItem);
                break;
            }
        }
    } else {
        // Pour toutes les autres touches, utilisez le comportement par défaut
        QListWidget::keyPressEvent(event);
    }
}
