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

class Cheese_Pizza : public PizzaFactory {
public:
	Sauce* AddSauce()
	{
		return new Cheese_Sauce;
	}

	Dough* AddDough()
	{
		return new Thick_Dough;
	}

	Filling* AddFilling()
	{
		return new Cheese;
	}
};


class Hawaiian_Pizza : public PizzaFactory {
public:
	Sauce* AddSauce()
	{
		return new Barbecue_Sauce;
	}
	Dough* AddDough()
	{
		return new Thin_Dough;
	}
	Filling* AddFilling()
	{
		return new Chiken;
	}
};

class Meat_Pizza : public PizzaFactory {
public:
	Sauce* AddSauce()
	{
		return new Barbecue_Sauce;
	}
	Dough* AddDough()
	{
		return new Thin_Dough;
	}
	Filling* AddFilling()
	{
		return new Chiken;
	}
};

//********************************************************

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


//********************custom pizza*******************************

class CustomPizza {
private:
	Sauce* custom_sauce;
	Dough* custom_dough;
	Filling* custom_filling;

public:
	CustomPizza()
	{}
	~CustomPizza()
	{}

	void SetSauce(Sauce * cur_sauce)
	{
		custom_sauce = cur_sauce;
	}
	void SetDough(Dough * cur_dough)
	{
		custom_dough = cur_dough;
	}
	void SetFilling(Filling * cur_filling)
	{
		custom_filling = cur_filling;
	}

	void ShowPizza()
	{
		custom_sauce->info();
		std::cout << " ";
		custom_dough->info();
		std::cout << " ";
		custom_filling->info();
		std::cout << std::endl;
	}
};

class CustomPizzaBuilder {
protected:
	CustomPizza *pizza;

public:
	CustomPizzaBuilder()
	{
		pizza = new CustomPizza;
	}
	virtual ~CustomPizzaBuilder()
	{}

	CustomPizza* GetPizza()
	{
		return pizza;
	}

	//creat new pizza

	virtual void BuildSauce(Sauce*) = 0;
	virtual void BuildDough(Dough*) = 0;
	virtual void BuildFilling(Filling*) = 0;

};

class CustomPersonalPizza : public CustomPizzaBuilder {
public:
	CustomPersonalPizza() : CustomPizzaBuilder()
	{}
	~CustomPersonalPizza()
	{
		//		delete pizza;
	}
	void BuildSauce(Sauce* cur_sauce)
	{
		pizza->SetSauce(cur_sauce);
	}
	void BuildDough(Dough* cur_dough)
	{
		pizza->SetDough(cur_dough);
	}
	void BuildFilling(Filling* cur_filling)
	{
		pizza->SetFilling(cur_filling);
	}
};

class TakeOrder {
private:
	CustomPizzaBuilder* pizzabuilder;
public:
	TakeOrder()
	{}
	~TakeOrder()
	{}

	void SetPizzaBuilder(CustomPizzaBuilder* b)
	{
		pizzabuilder = b;
	}

	CustomPizza* GetPizza()
	{
		return pizzabuilder->GetPizza();
	}

	void ConstructPizza(Sauce* c_sauce, Dough* c_dough, Filling* c_filling)
	{
		//ьс creat new pizza
		pizzabuilder->BuildSauce(c_sauce);
		pizzabuilder->BuildDough(c_dough);
		pizzabuilder->BuildFilling(c_filling);
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
	std::vector<Make_Order* > our_pizzas;
	std::vector<CustomPizza* > custom_pizzas;
	for (int i = 0; i < n; ++i)
	{
		Order order;
		TakeOrder t_order;

		std::cout << "If you want choose one of our pizzas press 1" << std::endl;
		std::cout << "If you want to make pizza yourself press 2" << std::endl;
		int k;
		std::cin >> k;
		if (k == 1)
		{
			std::cout << "press h - Hawaiian Pizza, m - Meat Pizza, c - Cheese Pizza" << std::endl;
			char c;
			std::cin >> c;
			Hawaiian_Pizza h_pizza;
			Meat_Pizza m_pizza;
			Cheese_Pizza c_pizza;
			Make_Order * h_pi;
			Make_Order * m_pi;
			Make_Order * c_pi;
			switch (c)
			{
			case 'h':
				h_pi = order.creat_order(h_pizza);
				our_pizzas.push_back(h_pi);
				break;
			case 'm':
				m_pi = order.creat_order(m_pizza);
				our_pizzas.push_back(m_pi);
				break;
			case 'c':
				c_pi = order.creat_order(c_pizza);
				our_pizzas.push_back(c_pi);
				break;
			}
			std::cout << "Your pizza includes ";
			our_pizzas.front()->info();
			std::cout << std::endl;
			std::cout << "Your pizza in oven" << std::endl;
		}
		else {
			if (k == 2)
			{
				CustomPersonalPizza p_pizza;
				t_order.SetPizzaBuilder(&p_pizza);

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
				case 'c':
					cur_sauce = &c_s;
					break;
				case 'b':
					cur_sauce = &b_s;
					break;
				}

				switch (dou)
				{
				case 'k':
					cur_dough = &k_d;
					break;
				case 'n':
					cur_dough = &n_d;
					break;
				}

				switch (fil)
				{
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
				t_order.ConstructPizza(cur_sauce, cur_dough, cur_filling);
				CustomPizza* pizza = t_order.GetPizza();

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
