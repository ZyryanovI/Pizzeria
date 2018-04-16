#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

class Sauce {
public:
	virtual void info() = 0;
	virtual ~Sauce()
	{}
};

class Dough {
public:
	virtual void info() = 0;
	virtual ~Dough()
	{}
};

class Filling {
public:
	virtual void info() = 0;
	virtual ~Filling()
	{}
};

//**********************************************************

class Cheese_Sauce : public Sauce {
public:
	void info()
	{
		std::cout << "chees sauce";
	}
};

class Barbecue_Sauce : public Sauce {
public:
	void info()
	{
		std::cout << "barbecue sauce";
	}
};


class Thin_Dough : public Dough {
public:
	void info()
	{
		std::cout << ", thin dough";
	}
};

class Thick_Dough : public Dough {
public:
	void info()
	{
		std::cout << ", thick dough";
	}
};

class Ham : public Filling {
public:
	void info()
	{
		std::cout << ", ham";
	}
};

class Chiken : public Filling {
public:
	void info()
	{
		std::cout << ", chiken";
	}
};

class Pineapples : public Filling {
public:
	void info()
	{
		std::cout << ", pineapples";
	}
};

class Tomatoes : public Filling {
public:
	void info()
	{
		std::cout << ", tomatoes";
	}
};

class Cheese : public Filling {
public:
	void info()
	{
		std::cout << ", cheese";
	}
};

//***********************************************************

class PizzaFactory {
public:
	virtual Sauce* AddSauce() = 0;
	virtual Dough* AddDough() = 0;
	virtual Filling* AddFilling() = 0;
	virtual ~PizzaFactory()
	{}
};

//*********************************************************

class Cheese_PizzaFactory : public PizzaFactory {
public:
	Sauce* AddSauce()
	{
		Sauce * sause = new Cheese_Sauce;
		return sause;
	}

	Dough* AddDough()
	{
		Dough * dough = new Thick_Dough;
		return dough;
	}

	Filling* AddFilling()
	{
		Filling * filling = new Cheese;
		return filling;
	}
};


class Hawaiian_PizzaFactory : public PizzaFactory {
public:
	Sauce* AddSauce()
	{
		Sauce * sause = new Barbecue_Sauce;
		return sause;
	}
	Dough* AddDough()
	{
		Dough * dough = new Thin_Dough;
		return dough;
	}
	Filling* AddFilling()
	{
		Filling * filling = new Chiken;
		return filling;
	}
};

class Meat_PizzaFactory : public PizzaFactory {
public:
	Sauce* AddSauce()
	{
		Sauce * sause = new Barbecue_Sauce;
		return sause;
	}
	Dough* AddDough()
	{
		Dough * dough = new Thin_Dough;
		return dough;
	}
	Filling* AddFilling()
	{
		Filling * filling = new Chiken;
		return filling;
	}
};

//********************************************************

class Pizza {
public:
	void Add_dough(Dough *_dough)
	{
		dough = _dough;
	}
	void Add_filling(Filling * _filling)
	{
		filling = _filling;
	}
	void Add_sauce(Sauce *_sause)
	{
		sause = _sause;
	}
	Dough* Get_dough()
	{
		return dough;
	}
	Sauce* Get_sauce()
	{
		return sause;
	}
	Filling* Get_filling()
	{
		return filling;
	}

	void ShowPizza()
	{
		sause->info();
		dough->info();
		filling->info();
	}

private:
	Sauce * sause;
	Dough * dough;
	Filling * filling;
};

//************builder*********************************

class IPizzaBuilder {
protected:
	Pizza* pizza;

public:
	virtual ~IPizzaBuilder()
	{}
	virtual Pizza* GetPizza() = 0;
	virtual void Create_Pizza() = 0;
	virtual void BuildSauce(Sauce* sauce) = 0;
	virtual void BuildDough(Dough* dough) = 0;
	virtual void BuildFilling(Filling* filling) = 0;

};



//Custom Pizza builder*********************************

class CustomPizzaBuilder : public IPizzaBuilder{
protected:
	Pizza *pizza;

public:
	CustomPizzaBuilder() {}
	~CustomPizzaBuilder() {
		delete pizza;
	}
	Pizza* GetPizza()
	{
		return pizza;
	}

	void Create_Pizza()
	{
		pizza = new Pizza;
	}

	void BuildSauce(Sauce* sauce) {
		pizza->Add_sauce(sauce);
	}
	void BuildDough(Dough* dough) {
		pizza->Add_dough(dough);
	}
	void BuildFilling(Filling* filling) {
		pizza->Add_filling(filling);
	}

};

//Pizzeria for usual pizza**********************************

class Pizzeria {
public:
	Pizza * MakePizza(PizzaFactory &factory)
	{
		Pizza * ptr = new Pizza;
		ptr->Add_dough(factory.AddDough());
		ptr->Add_sauce(factory.AddSauce());
		ptr->Add_filling(factory.AddFilling());
		return ptr;
	}

private:
};

//***************

class Make_Order {
public:
	~Make_Order()
	{
		delete cur_sauce;
		delete cur_dough;
		for (int i = 0; i < vect_of_fill.size(); ++i)
		{
			delete vect_of_fill[i];
		}
	}
	void info()
	{
		cur_sauce->info();
		cur_dough->info();
		for (int i = 0; i < vect_of_fill.size(); ++i)
		{
			vect_of_fill[i]->info();
		}
	}
	Sauce* cur_sauce;
	Dough* cur_dough;
	std::vector<Filling* > vect_of_fill;
};

class Order {
public:
	Make_Order* creat_order(PizzaFactory &factory)
	{
		Make_Order* m_o = new Make_Order;
		m_o->cur_sauce = factory.AddSauce();
		m_o->cur_dough = factory.AddDough();
		m_o->vect_of_fill.push_back(factory.AddFilling());
		return m_o;
	}
};



int main()
{
	int n;
	std::string adress;
	std::cout << "enter your adress" << std::endl;
	std::cin >> adress;
	std::cout << "enter how many pizzas do you want: " << std::endl;
	std::cin >> n;
	std::vector<Pizza* > our_pizzas;
	std::vector<Pizza* > custom_pizzas;
	for (int i = 0; i < n; ++i)
	{
		Order order;

		std::cout << "If you want choose one of our pizzas press 1" << std::endl;
		std::cout << "If you want to make pizza yourself press 2" << std::endl;
		int k;
		std::cin >> k;
		if (k == 1)
		{
			std::cout << "press h - Hawaiian Pizza, m - Meat Pizza, c - Cheese Pizza" << std::endl;
			char c;
			std::cin >> c;
			Hawaiian_PizzaFactory h_pizza_factory;
			Meat_PizzaFactory m_pizza_factory;
			Cheese_PizzaFactory c_pizza_factory;
			Make_Order * h_pi;
			Make_Order * m_pi;
			Make_Order * c_pi;
			Pizzeria pizzeria;
			Pizza* cur_pizza;
			switch (c)
			{
			default:
				cur_pizza = pizzeria.MakePizza(h_pizza_factory);
				our_pizzas.push_back(cur_pizza);
				break;
			case 'h':
				cur_pizza = pizzeria.MakePizza(h_pizza_factory);
				our_pizzas.push_back(cur_pizza);
				break;
			case 'm':
				cur_pizza = pizzeria.MakePizza(m_pizza_factory);
				our_pizzas.push_back(cur_pizza);
				break;
			case 'c':
				cur_pizza = pizzeria.MakePizza(c_pizza_factory);
				our_pizzas.push_back(cur_pizza);
				break;
			}
			std::cout << "Your pizza includes ";
			cur_pizza->ShowPizza();
			std::cout << std::endl;
			std::cout << "Your pizza in oven" << std::endl;
		}
		else {
			if (k == 2)
			{
				std::cout << "Choose your sause: c - cheese, b - barbecue: " << std::endl;
				char sau;
				std::cin >> sau;
				std::cout << std::endl;
				std::cout << "Choose your dought: k - for thick, n - for thin" << std::endl;
				char dou;
				std::cin >> dou;
				std::cout << std::endl;
				std::cout << "Choose your filling: h - ham, c - chicken, t - tomatoes, p -pineappels" << std::endl;
				char fil;
				std::cin >> fil;

				Sauce* cur_sauce;
				Dough* cur_dough;
				Filling* cur_filling;

				Cheese_Sauce c_s;
				Barbecue_Sauce b_s;
				Thin_Dough n_d;
				Thick_Dough k_d;
				Chiken chick;
				Ham ham;
				Tomatoes tom;
				Pineapples pin;

				switch (sau)
				{
				default:
					cur_sauce = &c_s;
					break;
				case 'c':
					cur_sauce = &c_s;
					break;
				case 'b':
					cur_sauce = &b_s;
					break;
				}

				switch (dou)
				{
				default:
					cur_dough = &k_d;
					break;
				case 'k':
					cur_dough = &k_d;
					break;
				case 'n':
					cur_dough = &n_d;
					break;
				}

				switch (fil)
				{
				default:
					cur_filling = &ham;
					break;
				case 'h':
					cur_filling = &ham;
					break;
				case 'c':
					cur_filling = &chick;
					break;
				case 't':
					cur_filling = &tom;
					break;
				case 'p':
					cur_filling = &pin;
					break;
				}
				CustomPizzaBuilder * builder = new CustomPizzaBuilder;
				builder->Create_Pizza();
				builder->BuildSauce(cur_sauce);
				builder->BuildDough(cur_dough);
				builder->BuildFilling(cur_filling);
				Pizza * pizza = builder->GetPizza();
				custom_pizzas.push_back(pizza);

				std::cout << "Your pizza includes: ";
				pizza->ShowPizza();
				std::cout << std::endl;
				std::cout << "Your pizza in oven" << std::endl;
			}
			else
			{
				if ((k != 1) && (k != 2))
				{
					std::cout << "Try again" << std::endl;
					--i;
				}
			}
		}
	}

	std::cout << "We made your order, the deliverer is ready to be delivered to the address " << adress<< std::endl;



	return 0;
}
