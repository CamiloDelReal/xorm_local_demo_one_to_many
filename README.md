# XOrm persistance with One to Many relationship
One to Many relationship using XOrm library

## This project will not be maintenance anymore
I am not working for Qt since a while and updates started to become hard after so much changes in Qt 6

### Features
- Members
  * CRUD operations
- Projects
  * CRUD operations
- MVVM architecture

### Entity relationship diagram
<p float="left">
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_many/blob/develop/design/exported_diagrams/persistence.jpg" width="80%" height="80%" />
</p>

### Entities definition

	class Member : public QObject, public XTableModel<Member>
	{
		Q_OBJECT

		Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString job READ job WRITE setJob NOTIFY jobChanged)

		Q_PROPERTY(QList<Project*> projects READ projects WRITE setProjects NOTIFY projectsChanged)

		X_TABLE_NAME("members")
		X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
					   X_FIELD(name),
					   X_FIELD(job))
		X_FOREIGN_LISTS(X_FOREIGN_LIST(Project, memberId, guid, projects))

	public:
		explicit Member(QObject *parent = nullptr);
		Member(const quint64 &guid, const QString &name, const QString &job, QObject *parent = nullptr);
		Member(const QString &name, const QString &job, QObject *parent = nullptr);
		Member(const Member &other);

		~Member();

		Member& operator=(const Member &other);

		quint64 guid() const;
		QString name() const;
		QString job() const;

		QList<Project*> projects() const;

	public slots:
		void setGuid(const quint64 &guid);
		void setName(const QString &name);
		void setJob(const QString &job);

		void setProjects(QList<Project*> projects);

	signals:
		void guidChanged(const quint64 &guid);
		void nameChanged(const QString &name);
		void jobChanged(const QString &job);

		void projectsChanged(QList<Project*> projects);

	private:
		quint64 m_guid;
		QString m_name;
		QString m_job;

		QList<Project*> m_projects;

		void clearProjects();
	};
	
	class Project : public QObject, public XTableModel<Project>
	{
		Q_OBJECT

		Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
		Q_PROPERTY(quint64 memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)

		X_TABLE_NAME("projects")
		X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
					   X_FIELD(name),
					   X_FIELD(description),
					   X_FIELD(memberId, "member_id", X_FOREIGN_KEY(Member, X_CASCADE, X_CASCADE)))

	public:
		explicit Project(QObject *parent = nullptr);
		Project(const QString &name, const QString &description, QObject *parent = nullptr);
		Project(const QString &name, const QString &description, const quint64 &memberId, QObject *parent = nullptr);
		Project(const quint64 &guid, const QString &name, const QString &description, const quint64 &memberId, QObject *parent = nullptr);
		Project(const Project &other);

		Project& operator=(const Project &other);

		quint64 guid() const;
		QString name() const;
		QString description() const;
		quint64 memberId() const;

	public slots:
		void setGuid(const quint64 &guid);
		void setName(const QString &name);
		void setDescription(const QString &description);
		void setMemberId(const quint64 &memberId);

	signals:
		void guidChanged(const quint64 &guid);
		void nameChanged(const QString &name);
		void descriptionChanged(const QString &description);
		void memberIdChanged(const quint64 &memberId);

	private:
		quint64 m_guid;
		QString m_name;
		QString m_description;
		quint64 m_memberId;
	};
	
### Screenshots
<p float="left">
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_many/blob/develop/screenshots/sshot-1.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_many/blob/develop/screenshots/sshot-2.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_many/blob/develop/screenshots/sshot-3.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_many/blob/develop/screenshots/sshot-4.png" width="30%" height="30%" />
</p>