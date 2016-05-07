#pragma once


class CounterOfTypeID {
public:
	static U32 counter;
};


//Class that gives an unique ID for every type. IDs are dependent on request order.
template<class C>
class TypeID {
public:

	//Returns an ID unique to type C.
	static U32 getType(){
		if (!num) num = ++CounterOfTypeID::counter;
		return num;
	}

	

private:
	static U32 num;
	
};

template<class C>
typename U32 TypeID<C>::num = 0;



struct CounterOfRenderLayerID {
	static U32 counter;
};


//Class that is used to identify RenderLayers based on renderType. 
//Class works like TypeID, but has to be inited. If getID is called before init(), returns 0.
template<class C>
class RenderLayerID {
public:

	static U32 getID() {
		return ID;
	}


	//Inits the ID for class C. Amt is amount of IDs to allocate for this type. Must be at least 1
	static void init(U32 amt) {
		ID = CounterOfRenderLayerID::counter;
		CounterOfRenderLayerID::counter += amt;
	}

private:
	static U32 ID;
};

template<class C>
U32 RenderLayerID<C>::ID = 0;


