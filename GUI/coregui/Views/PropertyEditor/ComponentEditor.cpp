// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditor.cpp
//! @brief     Implements class ComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "ComponentEditor.h"
#include "ComponentEditorPrivate.h"
#include "qtpropertybrowser.h"
#include "GUIHelpers.h"
#include "ParameterizedItem.h"
#include "SessionModel.h"
#include "GroupItem.h"
#include "GroupProperty.h"

#include <QVBoxLayout>
#include <QVariant>
#include <QDebug>

ComponentEditor::ComponentEditor(ComponentEditorFlags::PresentationType flags, QWidget *parent)
    : QWidget(parent)
    , m_d(new ComponentEditorPrivate(flags, this))
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("ComponentEditor"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_d->m_browser);

    connectManager();
}

ComponentEditor::~ComponentEditor()
{
}

//! Sets editor to display all recursive properties of given item
void ComponentEditor::setItem(ParameterizedItem *item, const QString &group_name)
{
    clearEditor();
    if(!item) return;

    connectModel(item->model());

    QtVariantProperty *groupVariantProperty = m_d->processPropertyGroupForName(group_name);

    foreach (ParameterizedItem *childItem, componentItems(item)) {
        updateEditor(childItem, groupVariantProperty);
    }
}


//! Main function to run through ParameterizedItem tree and fill editor with
//! properties
void ComponentEditor::updateEditor(ParameterizedItem *item,
                                   QtVariantProperty *parentProperty)
{
    if (QtVariantProperty *childProperty
        = m_d->processPropertyForItem(item, parentProperty)) {
        parentProperty = childProperty;
    }

    foreach (ParameterizedItem *childItem, componentItems(item)) {
        updateEditor(childItem, parentProperty);
    }
}

//! Clear editor from all properties, ready to accept new items
void ComponentEditor::clearEditor()
{
    disconnect();
    disconnectManager();
    m_d->clear();
    connectManager();
}

//! Propagates data from ParameterizedItem to editor
void ComponentEditor::onDataChanged(const QModelIndex &topLeft,
                                    const QModelIndex &bottomRight,
                                    const QVector<int> &roles)
{
    if (topLeft != bottomRight)
        return;

    SessionModel *model = qobject_cast<SessionModel *>(sender());
    Q_ASSERT(model);
    ParameterizedItem *item = model->itemForIndex(topLeft);
    Q_ASSERT(item);

    qDebug() << " ComponentEditor::onDataChanged" << m_d->m_presentationType
             << roles << item->modelType() << item->displayName();

    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        // updating editor's property appearance (tooltips, limits)
        if (roles.contains(Qt::UserRole)) {
            m_d->updatePropertyAppearance(property, PropertyAttribute::fromItem(item));
        }

        // updating editor's property values
        if (roles.contains(Qt::DisplayRole) || roles.contains(Qt::EditRole)) {
            disconnectManager();
            property->setValue(item->value());
            connectManager();

            if(item->modelType() == Constants::GroupItemType) {
                m_d->cleanChildren(item);
                updateEditor(item, m_d->getPropertyForItem(item->parent()));
            }

        }
    }
}

//! Updates the editor starting from given ParameterizedItem's parent.
//! Editor should know already about given item (i.e. corresponding
//! QtVariantProperty should exist.
void ComponentEditor::onRowsInserted(const QModelIndex &parent, int first,
                                     int last)
{
    qDebug() << "ComponentEditor::onRowsInserted" << parent << first << last;
    SessionModel *model = qobject_cast<SessionModel *>(sender());

    ParameterizedItem *item = model->itemForIndex(parent);
    Q_ASSERT(item);

    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        updateEditor(item, property);
    }
}

//! Propagates value from the editor to ParameterizedItem
void ComponentEditor::onQtPropertyChanged(QtProperty *property,
                                          const QVariant &value)
{
    qDebug() << "ComponentEditor::onQtPropertyChanged" << property << value;
    if (ParameterizedItem *item = m_d->getItemForProperty(property)) {
        Q_ASSERT(item);
        disconnectModel(item->model());
        item->setValue(value);
        connectModel(item->model());
    }
}

//! Returns list of children suitable for displaying in ComponentEditor.
QList<ParameterizedItem *>
ComponentEditor::componentItems(ParameterizedItem *item) const
{
    QList<ParameterizedItem *> result;
    foreach (ParameterizedItem *child, item->childItems()) {
        if (!child->isVisible())
            continue;
        if (child->modelType() == Constants::PropertyType) {
            result.append(child);
        }
        if (child->modelType() == Constants::GroupItemType) {
            result.append(child);
        }
        if (item->modelType() == Constants::GroupItemType) {
            foreach (ParameterizedItem *childOfChild, child->childItems()) {
                result.append(childOfChild);
            }
        }
    }

    return result;
}


void ComponentEditor::disconnectModel(SessionModel *model)
{
    if(!model) return;

    disconnect(
        model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &,
                                  const QVector<int> &)),
        this, SLOT(onDataChanged(const QModelIndex &, const QModelIndex &,
                                 const QVector<int> &)));

    disconnect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this,
               SLOT(onRowsInserted(const QModelIndex &, int, int)));
}

void ComponentEditor::connectModel(SessionModel *model)
{
    if(!model) return;

    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &,
                                      const QVector<int> &)),
            this, SLOT(onDataChanged(const QModelIndex &, const QModelIndex &,
                                     const QVector<int> &)),
            Qt::UniqueConnection);

    connect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this,
            SLOT(onRowsInserted(const QModelIndex &, int, int)),
            Qt::UniqueConnection);
}

void ComponentEditor::disconnectManager()
{
    disconnect(m_d->m_manager,
               SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
               SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)));
}

void ComponentEditor::connectManager()
{
    connect(m_d->m_manager,
            SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
            SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)),
            Qt::UniqueConnection);
}
