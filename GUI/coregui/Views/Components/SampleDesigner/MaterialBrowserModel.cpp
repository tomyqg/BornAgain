#include "MaterialBrowserModel.h"
#include "DesignerHelper.h"
#include "MaterialManager.h"
#include "HomogeneousMaterial.h"
#include <QColor>
#include <QtScript>
#include "Types.h"


#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif

MaterialBrowserModel::MaterialBrowserModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_selected_row(-1)
{
    UpdateMaterials();
}


MaterialBrowserModel::~MaterialBrowserModel()
{
    std::cout << "MaterialBrowserModel::~MaterialBrowserModel()" << std::endl;
}


// collecting info about defined materials
void MaterialBrowserModel::UpdateMaterials()
{
    std::cout << "MaterialBrowserModel::UpdateMaterials() -> nmaterials " << MaterialManager::getNumberOfMaterials() << std::endl;
    for(MaterialManager::iterator it = MaterialManager::instance().begin(); it!= MaterialManager::instance().end(); ++it) {
        const IMaterial *m = (*it).second;
        if(m_mat_color.contains(m)) continue;
        std::cout << " MaterialBrowserModel::UpdateMaterials() -> getting new material " << m->getName() << std::endl;
        m_mat_color[m] = suggestMaterialColor( QString(m->getName().c_str()) );
        m_nrow_mat.append(m);
    }
    emit layoutChanged();
}


void MaterialBrowserModel::RemoveMaterials(const QModelIndexList &index_list)
{
    if( !index_list.size() ) return;

    for(int i=0; i<index_list.size(); ++i) {
        int nrow = index_list[i].row();
        const IMaterial *mat = m_nrow_mat[nrow];
        std::cout << "MaterialBrowserModel::RemoveMaterial(int nrow) -> removing material " << nrow << " " << mat->getName() << std::endl;
        MaterialManager::instance().deleteMaterial(mat->getName());
        m_mat_color.remove(mat);
        m_nrow_mat[nrow] = 0;
    }

    QVector<const IMaterial *> tmp;
    for(int i=0; i<m_nrow_mat.size(); ++i) {
        if( m_nrow_mat[i] != 0 ) tmp.append(m_nrow_mat[i]);
    }
    m_nrow_mat = tmp;

    emit layoutChanged();
}


int MaterialBrowserModel::rowCount(const QModelIndex & /*parent*/) const
 {
    return MaterialManager::getNumberOfMaterials();
 }


int MaterialBrowserModel::columnCount(const QModelIndex & /*parent*/) const
 {
     return NumberOfMaterialProperties;
 }


QVariant MaterialBrowserModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= m_nrow_mat.size() ) {
        std::cout << "MaterialBrowserModel::data() -> 1.1 XXX Empty???" << std::endl;
        return QVariant();
    }
    const HomogeneousMaterial *mat = dynamic_cast<const HomogeneousMaterial *>(m_nrow_mat.at(index.row()));
    Q_ASSERT(mat);

    if (role == Qt::DisplayRole)
    {
        switch(index.column()) {
        case MaterialName:
            return QString(mat->getName().c_str());
        case MaterialIndexReal:
            return QString::number(mat->getRefractiveIndex().real());
        case MaterialIndexImag:
            return QString::number(mat->getRefractiveIndex().imag());
        case MaterialTitle:
            return QString();
        default:
            return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);
        }
    } else if (role == Qt::DecorationRole && index.column() == 0) {
        return m_mat_color[mat];
    } else if (role == Qt::CheckStateRole && index.column() == 0) {
        if(index.row() == m_selected_row) return Qt::Checked;
        return Qt::Unchecked;
    }


    return QVariant();
}


QVariant MaterialBrowserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case MaterialName:
                return QString("Name");
            case MaterialIndexReal:
                return QString("Index::real");
            case MaterialIndexImag:
                return QString("Index::imag");
            case MaterialTitle:
                return QString("Comment");
            }
        } else if (orientation == Qt::Vertical) {
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}


bool MaterialBrowserModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole) {
        if(index.row() >= m_nrow_mat.size() ) {
            std::cout << "MaterialBrowserModel::setData() -> 1.1 XXX Empty???" << std::endl;
            return false;
        }
        const HomogeneousMaterial *mat = dynamic_cast<const HomogeneousMaterial *>(m_nrow_mat.at(index.row()));
        Q_ASSERT(mat);

        complex_t refractiveIndex;
        bool status(true);
        double double_value;

        switch(index.column()) {
        case MaterialName:
            std::cout << " MaterialBrowserModel::setData() -> 1.1 " << value.toString().toStdString() << std::endl;
            if( !value.toString().size()) {
                emit SetDataMessage("Material should have non empty name");
                return false;
            }
            status = MaterialManager::instance().setMaterialName(mat->getName(), value.toString().toStdString());
            if(!status) {
                emit SetDataMessage("Already existing name");
                return false;
            }
            break;
        case MaterialIndexReal:

            //double_value = getDoubleValue(value, status);
            double_value = evaluateDoubleValue(value, status);
            std::cout << " MaterialBrowserModel::setData() -> 1.2 " << double_value << " result " << status << std::endl;
            if(!status) {
                emit SetDataMessage("Can't convert value to double");
                return false;
            }
            refractiveIndex = mat->getRefractiveIndex();
            refractiveIndex = complex_t(double_value, refractiveIndex.imag());
            status = MaterialManager::instance().setMaterialRefractiveIndex(mat->getName(), refractiveIndex);
            if(!status) {
                emit SetDataMessage("Can't set given value of RefractiveIndex");
                return false;
            }


            break;
        case MaterialIndexImag:
            //double_value = value.toDouble(&status);
            double_value = evaluateDoubleValue(value, status);
            std::cout << " MaterialBrowserModel::setData() -> 1.2 " << double_value << " result " << status << std::endl;
            if(!status) {
                emit SetDataMessage("Can't convert value to double");
                return false;
            }
            refractiveIndex = mat->getRefractiveIndex();
            //refractiveIndex.imag()=double_value;
            //refractiveIndex.imag(double_value);
            refractiveIndex = complex_t(refractiveIndex.real(), double_value);
            status = MaterialManager::instance().setMaterialRefractiveIndex(mat->getName(), refractiveIndex);
            if(!status) {
                emit SetDataMessage("Can't set given value of RefractiveIndex");
                return false;
            }

            break;
        case MaterialTitle:
            emit SetDataMessage("Not implemented ;)");
            break;
        default:
            break;
        }
        return true;
    } else if(role == Qt::CheckStateRole)  {
        if(m_selected_row == index.row()) {
            resetSelection();
        } else {
            m_selected_row = index.row();
            emit layoutChanged();
        }
        return true;
    }
    return true;
}


double MaterialBrowserModel::getDoubleValue(const QVariant &variant, bool &status)
{
    return variant.toDouble(&status);
}

double MaterialBrowserModel::evaluateDoubleValue(const QVariant &variant, bool &status)
{
    QString formula = variant.toString();
    if( !formula.size() ) {
        status = false;
        return 0.0;
    }
    QScriptEngine myEngine;
    QScriptValue x = myEngine.evaluate(formula);
    if( !x.isNumber()) {
        status = false;
        return 0.0;
    }
    return x.toNumber();
}



Qt::ItemFlags MaterialBrowserModel::flags(const QModelIndex & /*index*/) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable ;
}


QColor MaterialBrowserModel::suggestMaterialColor(const QString &name)
{
    if(name == QStringLiteral("Air") ) {
        return QColor(176, 226, 255);
    } else if(name == QStringLiteral("Substrate") ) {
        return QColor(205,102,0);
    } else if ( name == QStringLiteral("Default") ) {
        return QColor(Qt::green);
    }
    return DesignerHelper::getRandomColor();
}


MaterialProperty MaterialBrowserModel::getSelectedMaterialProperty()
{
    if( !hasSelection() ) {
        return MaterialProperty();
    } else {
        const IMaterial *mat = m_nrow_mat.at(m_selected_row);
        MaterialProperty p;
        p.setName(QString(mat->getName().c_str()));
        p.setColor(m_mat_color[mat]);
        return p;
    }
}


MaterialProperty MaterialBrowserModel::getDefaultMaterialProperty()
{
    const IMaterial *mat = MaterialManager::getMaterial("Default");
    MaterialProperty matProperty;
    if(mat) {
        matProperty.setName(QString(mat->getName().c_str()));
        matProperty.setColor(m_mat_color[mat]);
    }
    return matProperty;
}
