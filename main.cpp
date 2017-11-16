#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

enum ColorEnum
{
	Aquarius,
	Brown,
	Coral,
	Teal,
};

Q_DECLARE_METATYPE(ColorEnum)

class Object:
	public QObject
{
	Q_OBJECT

public:
	Q_ENUM(ColorEnum)
//	Q_ENUMS(ColorEnum)
//	inline Q_DECL_CONSTEXPR const QMetaObject *qt_getEnumMetaObject(ColorEnum) Q_DECL_NOEXCEPT
//	{
//		return &staticMetaObject;
//	}
//	inline Q_DECL_CONSTEXPR const char *qt_getEnumName(ColorEnum) Q_DECL_NOEXCEPT
//	{
//		return "ColorEnum";
//	}

	enum FruitEnum
	{
		Apple,
		Banana,
		Coconut,
		Orange,
	};
	Q_ENUM(FruitEnum)
//	Q_ENUMS(FruitEnum)
	// why copy-paste not work???
//	inline Q_DECL_CONSTEXPR const QMetaObject *qt_getEnumMetaObject(FruitEnum) Q_DECL_NOEXCEPT
//	{
//		return &staticMetaObject;
//	}
//	inline Q_DECL_CONSTEXPR const char *qt_getEnumName(FruitEnum) Q_DECL_NOEXCEPT
//	{
//		return "FruitEnum";
//	}

	enum NameEnum
	{
		Adam,
		Bell,
		Chopin,
		Newtown,
	};
	Q_ENUM(NameEnum)

	Q_INVOKABLE static QVariant fruitToVariant(FruitEnum enumValue)
	{
		return QVariant::fromValue(enumValue);
	}

	Q_INVOKABLE static QVariant nameToVariant(NameEnum enumValue)
	{
		return QVariant::fromValue(enumValue);
	}

	template<typename T>
	static QVariant variantOf(T enumValue)
	{
		return QVariant::fromValue(enumValue);
	}

	template<typename T>
	static const char* keyOf(T enumValue)
	{
		auto &meta = Object::staticMetaObject;
		QMetaEnum me = meta.enumerator(meta.indexOfEnumerator(qt_getEnumName(enumValue)));
		return me.valueToKey(enumValue);
	}
};

static QObject* objectSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	return new Object();
}

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	Object::FruitEnum e = Object::Coconut;
	qDebug() << "toString implicit:" << e;
	qDebug() << "toString by arg:" << QStringLiteral("%1").arg(e);
	qDebug() << "Variant constructor:" << QVariant(e);
	qDebug() << "Variant explicit:" << QVariant::fromValue(e);
	qDebug() << "Variant toString explicit:" << QVariant::fromValue(e).toString();
	qDebug() << "Variant toByteArray explicit:" << QVariant::fromValue(e).toByteArray();
	qDebug() << "Variant toInt explicit:" << QVariant::fromValue(e).toInt();
	qDebug() << "Variant toDouble explicit:" << QVariant::fromValue(e).toDouble();

	auto meta = Object::staticMetaObject;
//	QMetaEnum me = meta.enumerator(meta.indexOfEnumerator(qt_getEnumName(e)));
	QMetaEnum me = meta.enumerator(1); // select enumerator NameEnum to get Coconut -> Chpoin
	const char *key = me.valueToKey(e);
	qDebug() << "QMetaEnum value-key map:" << key << "=" << int(e);
	qDebug() << "VariantOf:" << Object::variantOf(e);
	qDebug() << "KeyOf:" << Object::keyOf(e);

	qmlRegisterType<Object>("My", 1, 0, "Object");
	qmlRegisterUncreatableMetaObject(Object::staticMetaObject, "My", 1, 0, "ObjectMetaObject", "Access to enums");
	qmlRegisterUncreatableType<Object>("My", 1, 0, "ObjectStatic", "Access to statics....enums");
	qmlRegisterSingletonType<Object>("My", 1, 0, "ObjectSingleton", objectSingletonProvider);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

#include "main.moc"
