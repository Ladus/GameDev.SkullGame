class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};