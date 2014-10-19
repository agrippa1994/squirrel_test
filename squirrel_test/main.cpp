#include <squirrel.h> 
#include <sqstdio.h> 
#include <sqstdaux.h> 
#include <sqrat.h>

#include <iostream>
#include <thread>
#include <mutex>

#include <stdarg.h>

#ifdef _MSC_VER
#pragma comment (lib ,"squirrel.lib")
#pragma comment (lib ,"sqstdlib.lib")
#endif

#define LOG std::cout << "[C++-DEBUG] " __FUNCTION__ << std::endl;

using namespace Sqrat;

class Player
{
	float m_x = 0, m_y = 1, m_z = 2;
	Function m_positionChangedCallback;

public:
	Player()
	{
		LOG
	}

	Player(SQFloat fx, SQFloat fy, SQFloat fz)
	{
		LOG
		m_x = fx, m_y = fy, m_z = fz;
	}

	~Player()
	{
		LOG
	}

	void setPosition(SQFloat fx, SQFloat fy, SQFloat fz)
	{
		LOG
	
		m_x = fx, m_y = fy, m_z = fz;

		if (!m_positionChangedCallback.IsNull())
			m_positionChangedCallback(m_x, m_y, m_z);
	}

	SQFloat x()
	{
		LOG
		return m_x;
	}

	SQFloat y()
	{
		LOG
		return m_y;
	}

	SQFloat z()
	{
		LOG
		return m_z;
	}
	
	Function positionChangedCallback()
	{
		LOG
		return m_positionChangedCallback;
	}

	void setX(SQFloat _x)
	{
		LOG
		
		m_x = _x;

		if (!m_positionChangedCallback.IsNull())
			m_positionChangedCallback(m_x, m_y, m_z);
	}

	void setY(SQFloat _y)
	{
		LOG
		
		m_y = _y;

		if (!m_positionChangedCallback.IsNull())
			m_positionChangedCallback(m_x, m_y, m_z);
	}

	void setZ(SQFloat _z)
	{
		LOG
		
		m_z = _z;

		if (!m_positionChangedCallback.IsNull())
			m_positionChangedCallback(m_x, m_y, m_z);
	}

	void setPositionChangedCallback(Function func)
	{
		LOG
		m_positionChangedCallback = func;
	}

	void releasePositionChangedCallback()
	{
		m_positionChangedCallback.Release();
	}
};


int main()
{
	HSQUIRRELVM vm;
	vm = sq_open(8192);

	Sqrat::DefaultVM().Set(vm);

	sq_setprintfunc(vm, [](HSQUIRRELVM v, const SQChar *s, ...)
	{
		va_list vlist;
		va_start(vlist, s);
		vprintf(s, vlist);
		va_end(vlist);

		std::cout << std::endl;
	}, NULL);

	

	try
	{
		{
			RootTable().Bind("Player",
			Class<Player>()
			.Ctor()
			.Ctor<SQFloat, SQFloat, SQFloat>()
			.Prop("x", &Player::x, &Player::setX)
			.Prop("y", &Player::y, &Player::setY)
			.Prop("z", &Player::z, &Player::setZ)
			.Prop("positionChangedCallback", &Player::positionChangedCallback, &Player::setPositionChangedCallback)
			.Func("setPosition", &Player::setPosition)
			.Func("releasePositionChangedCallback", &Player::releasePositionChangedCallback)
			);
		}

		Script script;
		script.CompileFile("squirrel.nut");

		std::string error;
		script.Run(error);

		if (error.length())
		{
			std::cout << "Error: " << error << std::endl;
		}
		
	}
	catch (...)
	{
		std::cout << "Error!" << std::endl;
	}

	std::cin.get();
}