#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

enum ValType { VINT, VREAL, VSTRING, VBOOL, VERR };

class Value {
    ValType	T;
    bool    Btemp;
	int		Itemp;
	float   Rtemp;
    string	Stemp;
       
public:
    Value() : T(VERR), Btemp(false), Itemp(0), Rtemp(0.0), Stemp("") {}
    Value(bool vb) : T(VBOOL), Btemp(vb), Itemp(0), Rtemp(0.0), Stemp("") {}
    Value(int vi) : T(VINT), Btemp(false), Itemp(vi), Rtemp(0.0), Stemp("") {}
	Value(float vr) : T(VREAL), Btemp(false), Itemp(0), Rtemp(vr), Stemp("") {}
    Value(string vs) : T(VSTRING), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(vs) {}
    
    
    ValType GetType() const { return T; }
    bool IsErr() const { return T == VERR; }
    bool IsInt() const { return T == VINT; }
    bool IsString() const { return T == VSTRING; }
    bool IsReal() const {return T == VREAL;}
    bool IsBool() const {return T == VBOOL;}
    
    int GetInt() const { if( IsInt() ) return Itemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    string GetString() const { if( IsString() ) return Stemp; throw "RUNTIME ERROR: Value not a string"; }
    
    float GetReal() const { if( IsReal() ) return Rtemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    bool GetBool() const {if(IsBool()) return Btemp; throw "RUNTIME ERROR: Value not a boolean";}
    
    void SetType(ValType type)
    {
    	T = type;
	}
	
    void SetInt(int val)
    {
    	Itemp = val;
	}
	
	void SetReal(float val)
    {
    	Rtemp = val;
	}
	
	void SetString(string val)
    {
    	Stemp = val;
	}
	
	void SetBool(bool val)
    {
    	Btemp = val;
	}
	
	
	
	
    // add op to this
    Value operator+(const Value& op) const
    {
        
        bool ISINT = IsInt();
        
        bool x = true;
        bool t = true;
        
        
        x = ISINT;
        
        
        
        ///////////////////
    if (x && op.IsInt())/*if both true return*/{
        
        if(t){
        return Value(Itemp + op.GetInt());
        }
        	else
			{
			    return Value()/*return the value*/;
			    
			}
        
        }
       
       ////////////////////////
    else if (t && IsString() && (op.IsString() && t /*if they are true run*/)){
        
            return Value(Stemp + op.GetString())/*return the value*/;
    
    
    }
    
    //////////////////////////////////
    else if(IsReal() && op.IsReal() /* else if they are true run*/){
         int pub = Rtemp + op.GetReal()/*create variable for the return value*/;
        return Value(pub)/*return the value*/;
    }
    
    //////////////////////
    else if((t&& IsReal()) && op.IsInt() /*if they are true run add*/){
        
        return Value(Rtemp + op.GetInt())/*return the value*/;
    }
    
    
    /////////////////////////
    else if(t && IsInt() && op.IsReal()){
        float pub = Itemp + op.GetReal()/*create variable for the return value*/;
            return Value(pub)/*return the value*/;
        }
        
        
    ////////////////////
    else if( IsErr() || (op.IsErr() && t)){
        return Value()/*return the value*/;
    }
    
    
    /////////////////
    else/*else to return*/{
        return Value()/*return the value*/;
    }
    
    
    }
    
    
    // subtract op from this
    Value operator-(const Value& op) const;
    
    
    
    // multiply this by op
    Value operator*(const Value& op) const
    {
        bool x = true;
        
        if ((x && IsInt()) && op.IsInt() ==true /*both true and equal */){
            int val = Itemp * op.GetInt();
            return Value(val)/*return the value*/;
       }

    else if((x && IsReal()) && op.IsInt() == true /*both true and equal */){
        float val = Rtemp * op.GetInt();
        return Value(val)/*return the value*/;
    }


    else if(IsReal() && op.IsReal() == true /*both true and equal */){
         float val =Rtemp * op.GetReal();
        return Value(val) /*return the value*/;
    }    
    
    else if(IsInt() && op.IsReal() == true/*both true and equal */) {
        float val =Itemp * op.GetReal();
         return Value(val) /*return the value*/;
        }
        
        
    else if( (x && IsErr() )|| op.IsErr() == true/*both true and equal */){
     
        return Value() /*return the value*/;
        
            
        }
    
    
    else{
        return Value();
    }
    
}

    
    // divide this by op
    Value operator/(const Value& op) const;
    
    Value operator==(const Value& op) const{
        bool x = true;
        if ((x && IsInt()) && op.IsInt() == true){
            bool var = Itemp/*create variable for the return value*/;
            return Value(var)/*return the value*/;
       }
       
    else if (IsString() && op.IsString() == true){
        bool var = Stemp == op.GetString() /*create variable for the return value*/;
            return Value(var) /*return the value*/;
    }
    
    else if(IsReal() && op.IsReal() == true){
        bool var = Rtemp == op.GetReal() /*create variable for the return value*/;
        return Value(var) /*return the value*/;
    }

    else if((IsReal() && op.IsInt()) == true){
        bool var = Rtemp == op.GetInt()/*create variable for the return value*/;
        return Value(var)/*return the value*/ ;
    }
    
    else if(((x && IsInt() ) && op.IsReal()) == true){
        bool var = Itemp == op.GetReal()/*create variable for the return value*/;
            return Value(var) /*return the value*/;
        }
        
    else if((IsErr() || op.IsErr()) == true){
        return Value();
    }
    
    else{
        return Value()/*return the value*/;
    }
    
    }

	Value operator>(const Value& op) const;
	
	Value operator<(const Value& op) const;
	
	    
    friend ostream& operator<<(ostream& out, const Value& op){
        if( op.IsInt() ) out << op.Itemp;
        else if( op.IsString() ) out << op.Stemp;
        else if( op.IsReal()) out << fixed << showpoint << setprecision(2) << op.Rtemp;
        else if (op.IsBool()) {
        	if(op.GetBool()) cout << "true" ;
        	else{
        		cout << "false" ;
        	}
		}
		
        else out << "ERROR";
        return out;
        
    }
};


#endif