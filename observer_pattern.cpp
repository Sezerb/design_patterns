/****
 * Simple observer pattern.
 * A key notifier in a TV software notifies possible menus
 *  on the TV software when a button is pressed on the remote controller.
 * */

#include <iostream>
#include <vector>

/// OSDs (Menus) of TV
static const int MAIN_MENU = 1;
static const int IDLE_MENU = 0;

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
	virtual void registerObserver(Observer *o);
//	virtual void removeObserver(Observer *o);
	virtual void notifyObservers();
}

class KeyNotifier : public Subject
{
	int _key;
	vector<Observer*> _menuList;

public:
	void registerObserver(Observer* o){
		_menuList.push_back(o);
	}

	int notifyObservers(){
		for(auto &menu : _menuList){
			menu.update(_key);
		}
	}

	int setKey(int key){
		_key = key;
		//Notify all observers!
		notify();
	}
};

class MainMenu : public Observer{
	int _currMenu;
public:
	MainMenu(KeyNotifier* pKeyNotifier, int currMenu) : _currMenu(currMenu){
		/// Register observer to subject
		pKeyNotifier->registerObserver(this);
	}

	virtual bool update(int key){
		if(_currMenu == IDLE_MENU && key == KEY_MAIN_MENU){
			std::cout << "menu key: " << "Main Menu is opened" << std::endl;
			return true;
		}
		else{
			std::cout << "Main menu, do nothing!" << std::endl;
			return false;
		}
	}
};

class IdleMenu: public Observer{
	int _currMenu;

public:
	IdleMenu(KeyNotifier* pKeyNotifier, int currMenu) : _currMenu(currMenu){
		//Attach idle menu to key notifier.
		pKeyNotifier->registerObserver(this);
	}

	virtual bool update(int key){
		if(_currMenu == MAIN_MENU && key == KEY_EXIT){
			std::cout << "exit key: " << "Main Menu is closed" << std::endl;
			return true;
		}
		else{
			std::cout << "Idle menu, do nothing!" << std::endl;
			return false;
		}
	}	
	
};



int main(){
	KeyNotifier kn;
	MainMenu mm(&kn, 0);
	IdleMenu im(&kn, 0);
	
	//Open main menu
	kn.setKey(KEY_MAIN_MENU);

	//Do smth....

	//Close main menu
	kn.setKey(KEY_EXIT);
}