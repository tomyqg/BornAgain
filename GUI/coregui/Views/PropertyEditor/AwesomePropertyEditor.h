// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/AwesomePropertyEditor.h
//! @brief     Defines class AwesomePropertyEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef AWESOMEPROPERTYEDITOR_H
#define AWESOMEPROPERTYEDITOR_H

#include "WinDllMacros.h"
#include <QWidget>

class ParameterizedItem;
class AwesomePropertyEditorPrivate;
class ParameterizedIytem;
class QtProperty;
class QtVariantProperty;

//! property editor to display and modify properties of multiple ParameterizedItem
class BA_CORE_API_ AwesomePropertyEditor : public QWidget
{
    Q_OBJECT

public:
    enum EBrowserType {BROWSER_TREE_TYPE, BROWSER_GROUPBOX_TYPE, BROWSER_BUTTON_TYPE};
    enum EInsertMode {INSERT_AS_CHILD, INSERT_AFTER};
//    enum ESubItemsPolicy {SUBITEMS_SKIP, SUBITEMS_AS_CHILD, SUBITEMS_AFTER};

    AwesomePropertyEditor(QWidget *parent = 0, EBrowserType browser_type = BROWSER_TREE_TYPE);
    virtual ~AwesomePropertyEditor();

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    //! add multiple properties of ParameterizedItem
    void addItemProperties(ParameterizedItem *item, QtProperty *parent_qtproperty = 0);
    void addItemPropertiesToGroup(ParameterizedItem *item, const QString &group_name);

    //! add single ParameterizedItem property
    void addItemProperty(ParameterizedItem *item, const QString &property_name, QtProperty *parent_qtproperty = 0);

    void insertItemProperties(ParameterizedItem *item, QtVariantProperty *parent_qtproperty=0, EInsertMode insert_mode = INSERT_AFTER);
    void insertItemProperty(ParameterizedItem *item, const QString &property_name, QtVariantProperty *parent_qtproperty=0, EInsertMode insert_mode = INSERT_AFTER);

    //! add single ParameterizedItem property to group
    void addItemPropertyToGroup(ParameterizedItem *item, const QString &property_name, const QString &group_name);

    void setRecursive(bool recursive_flag);




    void clearEditor();

private slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);
    void onPropertyChanged(const QString &property_name);
    void onPropertyItemChanged(const QString &property_name);
    void removeSubProperties(QtProperty *property);

private:
    QtVariantProperty *createQtVariantProperty(ParameterizedItem *item, const QString &property_name);
    void insertQtVariantProperty(QtVariantProperty *qtVariantItem, QtVariantProperty *parent_qtproperty, EInsertMode insert_mode);

    AwesomePropertyEditorPrivate *m_d;
};


#endif // SAMPLEPROPERTYEDITOR_H
