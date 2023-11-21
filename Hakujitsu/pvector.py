class vec3 :
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
    
    def __add__(self, other):
        if isinstance(other, vec3):
            return vec3(self.x + other.x, self.y + other.y, self.z + other.z)
        else:
            raise TypeError("Unsupported operand type. The operand should be a Vector3 object.")
            
    def __sub__(self, other):
        if isinstance(other,vec3):
            return vec3(self.x - other.x, self.y - other.y, self.z - other.z)
    def __mul__(self, other):
        if isinstance(other,vec3):
            return self.x * other.x + self.y * other.y + self.z * other.z
        elif isinstance(other,float) | isinstance(other,int)  :
            return vec3(self.x*other,self.y*other,self.z*other)
        else:
            raise TypeError("Unsupported operand type. The operand should be a Vector3 object.")
    def __rmul__(self, other):
        if isinstance(other,vec3):
            return self.x * other.x + self.y * other.y + self.z * other.z
        elif isinstance(other,float) | isinstance(other,int) :
            return vec3(self.x*other,self.y*other,self.z*other)
        else:
            raise TypeError("Unsupported operand type. The operand should be a Vector3 object.")
    def mag(self):
        return pow((self.x*self.x+self.y*self.y+self.z*self.z),0.5)
    def normalize(self):
        a = pow((self.x*self.x+self.y*self.y+self.z*self.z),0.5)
        return vec3(self.x/a,self.y/a,self.z/a)
    def __truediv__(self,other):
        if isinstance(other,float) | isinstance(other,int):
            return vec3(self.x/other,self.y/other,self.z/other)
        else:
            return TypeError("Unsupported operand type. The operand should be a Vector3 object.")