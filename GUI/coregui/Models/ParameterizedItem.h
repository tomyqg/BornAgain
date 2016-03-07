// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedItem.h
//! @brief     Defines class ParameterizedItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERIZEDITEM_H_
#define PARAMETERIZEDITEM_H_

#include "WinDllMacros.h"
#include "item_constants.h"
#include "ModelMapper.h"
#include "AttLimits.h"

#include <memory>
#include <QObject>
#include <QVector>
#include <QVariant>
#include <QMetaType>

Q_DECLARE_METATYPE(AttLimits)

class SessionModel;


class SessionItemData;


class SessionTagInfo
{
public:
    inline SessionTagInfo() : name(QString()), min(0), max(-1), childCount(0) {}
    inline SessionTagInfo(QString n, int mi, int ma, QStringList mt = QStringList())
        :name(n)
        , min(mi)
        , max(ma)
        , childCount(0)
        , modelTypes(mt) {}
    QString name;
    int min;
    int max;
    int childCount;
    QStringList modelTypes;
    inline bool isValid() { return !name.isEmpty(); }
};


class BA_CORE_API_ ParameterizedItem : public QObject
{
    Q_OBJECT
    friend class SessionModel;

public:
    //! create new parameterized item and set model type
    explicit ParameterizedItem(QString modelType = QString());

    //! delete me and children
    virtual ~ParameterizedItem();

    ParameterizedItem *getItem(QString tag = QString(), int index = 0) const;

    QVector<ParameterizedItem *> getItems(QString tag = QString()) const;

    bool insertItem(int row, ParameterizedItem *item, const QString &tag);

    ParameterizedItem *takeItem(int row, const QString &tag);

    bool registerTag(QString name, int min = 0, int max = -1, QStringList modelTypes = QStringList());

    SessionTagInfo getTagInfo(const QString &name) const;

    //! retrieve data of given column, return invalid qvariant when out of range
    QVariant data(int role) const;

    //! set data in the given column, return true when successful, notify model if present
    //! we only support one role
    virtual bool setData(int role, const QVariant &value);


    // data manipulation

    //! return variant stored in data column
    QVariant value() const;

    //! set data column
    bool setValue(QVariant value);

    //! check if data is set
    bool hasData(int column);

    //! inform the model that something changed
    void emitValueChanged(QVector<int> roles = QVector<int>() << Qt::DisplayRole << Qt::EditRole);


    // labels

    //! user can set a name to item, which is stored in P_NAME property
    static const QString P_NAME;

    //! return a user definable name, if present, or returs displayName() otherwise
    QString itemName() const;

    //! set the item's name in the registered property P_NAME
    void setItemName(const QString &name);

    //! retrieve a unique name based on the type and an index (if needed to distinguish siblings)
    //! This name is primarely used for generating long parameter names (ParticleDistributionItem
    //! and fitting).
    QString displayName() const;

    //! retrieves the model type
    QString modelType() const;

    //! return a nice string representation of the data contained in this item
    virtual QString itemLabel() const;


    // members

    SessionModel *model() const;


    // navigation functions

    //! return index of this item
    QModelIndex index() const;

    //! retrieve parent item
    ParameterizedItem *parent() const;

    //! get number of child items
    int childItemCount() const;

    //! column count is equal for all items and is derived from session model
    int columnCount() const;

    //! retrieve child item in given row - take care of null pointer
    ParameterizedItem *childAt(int row) const;

    //! get row number of child
    int rowOfChild(ParameterizedItem *child) const;

    //! the index of this item from his parent
    int childNumber() const;


    // accessing children

    //! indicates if item has child items
    bool hasChildItems() const;

    //! returns the a list of child items
    QVector<ParameterizedItem *> childItems() const;

    //! Returns a pointer to the first child of the given type
    ParameterizedItem *getChildOfType(const QString &type) const;

    //! get pointer to irst child with given display name (take care of appended index number)
    ParameterizedItem* getChildByName(const QString &name) const;

    //! returns a list of children of a certain type
    QList<ParameterizedItem *> getChildrenOfType(const QString &model_type) const;

    //! returns a list of children of a certain type
    QList<ParameterizedItem *> getUnregisteredChildren() const;

    //! insert a child item at specified row
    virtual void insertChildItem(int row, ParameterizedItem *item);

    //! take child item (this removes it from the current item)
    virtual ParameterizedItem *takeChildItem(int row);

    //! indicates if the passed item can be set as a child item
    bool acceptsAsChild(const QString &child_name) const;

    //! get list of acceptable child object names
    QList<QString> acceptableChildItems() const;


    // registered properties

    //! insert child item and make it known to it, populate with default value
    //! TODO propertyattributes should now be set on the item itself
    ParameterizedItem *registerProperty(const QString &name, const QVariant &variant);

    //! check in its property map
    bool isRegisteredProperty(const QString &name) const;

    //! get the item of corresponding registered property
    ParameterizedItem * getPropertyItem(const QString &name) const;

    //! retrieve property
    QVariant getRegisteredProperty(const QString &name) const;

    //! update the property through the model
    void setRegisteredProperty(const QString &name, const QVariant &variant);

    //! emit signal that property is changed
    void emitPropertyChanged(const QString &name, QVector<int> roles = QVector<int>());

    //! unset property from this item
    void removeRegisteredProperty(const QString &name);


    // group properties

    //! register a new group property according to group name
    ParameterizedItem *registerGroupProperty(const QString &group_name,
                                             const Constants::ModelType &group_model);

    //! check if this group property exists
    bool isGroupProperty(const QString &name) const;

    //! set the group of the property, returns current item
    //! call without second parameter to get current item directly
    ParameterizedItem *setGroupProperty(const QString &name, const QString &value = QString()) const;

    //! returns current item of group property
    ParameterizedItem *getGroupItem(const QString &name, const QString &type = QString()) const;


    // attributes


    void setVisible(bool enabled);
    void setEnabled(bool enabled);
    void setEditable(bool enabled);

    bool isVisible() const;
    bool isEnabled() const;
    bool isEditable() const;

    AttLimits limits() const;
    void setLimits(AttLimits value);

    int decimals() const;
    void setDecimals(int n);

    QString toolTip() const;
    void setToolTip(QString tooltip);

    QString defaultTag() const;
    void setDefaultTag(QString tag);


    // helper

    //! checking constrains of ports
    virtual ParameterizedItem *getCandidateForRemoval(ParameterizedItem *new_comer);

    //! returns mapper of this item
    ModelMapper *mapper();

    //! sets the display name
    void setDisplayName(QString display_name);


protected:


    //! swap two children in member list
    //! use this to enforce a specific order when this matters
    void swapChildren(int first, int second);


private:
    //! used for display name to get the index of the item
    int getCopyNumberOfChild(const ParameterizedItem *p_item) const;


    //! called to set child to nullptr
    void childDeleted(ParameterizedItem *child);


    //! simple setter
    void setParentAndModel(ParameterizedItem *parent, SessionModel *model);


    //! set model of item and children
    void setModel(SessionModel *model);


    int tagStartIndex(const QString &name) const;

    QVariant readUserRoles(int role) const;

    bool canWriteUserRole(int role) const;

    void changeFlags(bool enabled, int flag);

    int flags() const;



    ParameterizedItem *mp_parent;
    SessionModel *m_model;

    QVector<ParameterizedItem *> m_children;
    QVector<SessionItemData> m_values;
    QVector<SessionTagInfo> m_tags;


    std::unique_ptr<ModelMapper> m_mapper;




    // end of refactored parameterized item

};

#endif /* PARAMETERIZEDITEM_H_ */
