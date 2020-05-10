/****
 * Simple observer pattern.
 * A key notifier in a TV software notifies possible menus
 *  on the TV software when a button is pressed on the remote controller.
 * */

#include <iostream>
#include <vector>

/// State of Menus/OSDs
static const int OFF = 0;
static const int ON = 1;

//Remote Controller Keys
static const int KEY_MAIN_MENU = 1;
static const int KEY_EXIT = 0;

/// Observer Interface
class Observer
{
public:
	virtual void update(int key) = 0;
};

/// Subject Interface
class Subject
{
public:
	virtual void registerObserver(Observer *o) = 0;
//	virtual void removeObserver(Observer *o) = 0;
	virtual void notifyObservers() = 0;
};

class KeyNotifier : public Subject
{
	int _key;
	std::vector<Observer*> _menuList;

public:
	void registerObserver(Observer* o){
		_menuList.push_back(o);
	}

	void notifyObservers(){
		for(const auto &menu : _menuList){
			menu->update(_key);
		}
	}

	void setKey(int key){
		_key = key;
		//Notify all observers!
		notifyObservers();
	}
};

class MainMenu : public Observer{
	int _state;
public:
	MainMenu(KeyNotifier* pKeyNotifier, int state) : _state(state){
		/// Register observer to subject
		pKeyNotifier->registerObserver(this);
	}

	void update(int key){
		if(_state == OFF && key == KEY_MAIN_MENU){
			std::cout << "Main Menu is opened" << std::endl;
			_state = ON;
		}
		else{
			std::cout << "Main menu, do nothing!" << std::endl;
		}
	}
};

class IdleMenu: public Observer{
	int _state;

public:
	IdleMenu(KeyNotifier* pKeyNotifier, int state) : _state(state){
		//Attach idle menu to key notifier.
		pKeyNotifier->registerObserver(this);
	}

	void update(int key){
		if(_state == OFF && key == KEY_MAIN_MENU){
			std::cout << "Main Menu is closed" << std::endl;
			_state = ON;
		}
		else{
			std::cout << "Idle menu, do nothing!" << std::endl;
		}
	}	
	
};



int main(){

	/// TV is starting...
	KeyNotifier kn;
	MainMenu mm(&kn, OFF);
	IdleMenu im(&kn, OFF); ///No menu at all, it's video screen.
	
	//Press Main Menu button
	kn.setKey(KEY_MAIN_MENU);
	
}