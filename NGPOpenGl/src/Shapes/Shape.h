class Shape {
public:
	virtual void draw()=0;
    virtual void updateUniforms()=0;
   virtual void Translate(glm::vec3& translate)=0;
   virtual void Scale(glm::vec3 scale)=0;
   virtual void Scale(float scale)=0;
   virtual void Rotate(float angle, glm::vec3 axis)=0;
   virtual void SetView(glm::mat4 view)=0;
   virtual void SetProj(glm::mat4 proj)=0;
   virtual void SetDimensions(float width, float height)=0;
   virtual void setModeTexture(int mode) = 0;
};