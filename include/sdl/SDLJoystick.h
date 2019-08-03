#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <SDL_joystick.h>
#include <SDL_events.h>
#include <SDL_log.h>
#include <map>
#include <vector>
#include <tuple>
#include <memory>

class Joystick {
public:
	explicit Joystick(int);
	~Joystick();

	bool isJoystick() const { return joystick_ != nullptr; }

	static int num() { return ::SDL_NumJoysticks(); }
	static void lock() { ::SDL_LockJoysticks(); }
	static void unlock() { ::SDL_UnlockJoysticks(); }
	static void update() { ::SDL_JoystickUpdate(); }

//	const char *getName() const { return ::SDL_JoystickNameForIndex(device_index_); }
//	SDL_JoystickGUID getDeviceGUID() const { return ::SDL_JoystickGetDeviceGUID(device_index_); }
//	uint16_t getDeviceVendor() const { return ::SDL_JoystickGetDeviceVendor(device_index_); }
//	uint16_t getDeviceProduct() const { return ::SDL_JoystickGetDeviceProduct(device_index_); }
//	uint16_t getDeviceProductVersion() const { return ::SDL_JoystickGetDeviceProductVersion(device_index_); }
//	SDL_JoystickType getDeviceType() const { return ::SDL_JoystickGetDeviceType(device_index_); }
//	SDL_JoystickID getDeviceInstanceID() const { return ::SDL_JoystickGetDeviceInstanceID(device_index_); }

	//extern DECLSPEC SDL_Joystick *SDLCALL SDL_JoystickOpen(int device_index);
	//extern DECLSPEC SDL_Joystick *SDLCALL SDL_JoystickFromInstanceID(SDL_JoystickID joyid);
	const char *getName() const { return ::SDL_JoystickName(joystick_); }
	SDL_JoystickGUID getGUID() const { return ::SDL_JoystickGetGUID(joystick_); }
	uint16_t getVendor() const { return ::SDL_JoystickGetVendor(joystick_); }
	uint16_t getProduct() const { return ::SDL_JoystickGetProduct(joystick_); }
	uint16_t getProductVersion() const { return ::SDL_JoystickGetProductVersion(joystick_); }
	SDL_JoystickType getType() const { return ::SDL_JoystickGetType(joystick_); }
	//extern DECLSPEC void SDLCALL SDL_JoystickGetGUIDString(SDL_JoystickGUID guid, char *pszGUID, int cbGUID);
	//extern DECLSPEC SDL_JoystickGUID SDLCALL SDL_JoystickGetGUIDFromString(const char *pchGUID);
	bool getAttached() const { return ::SDL_JoystickGetAttached(joystick_); }
	SDL_JoystickID getInstanceID() const { return ::SDL_JoystickInstanceID(joystick_); }
	int numAxes() const { return ::SDL_JoystickNumAxes(joystick_); }
	int numBalls() const { return ::SDL_JoystickNumBalls(joystick_); }
	int numHats() const { return ::SDL_JoystickNumHats(joystick_); }
	int numButtons() const { return ::SDL_JoystickNumButtons(joystick_); }

	bool isEventEnable() const { return ::SDL_JoystickEventState(SDL_QUERY) == SDL_ENABLE; }
	void setEventEnable() { ::SDL_JoystickEventState(SDL_ENABLE); }
	void setEventDisable() { ::SDL_JoystickEventState(SDL_IGNORE); }

	int16_t getAxis(int axis) const { return ::SDL_JoystickGetAxis(joystick_, axis); }
	int16_t getAxisInitialState(int axis) const {
		Sint16 state;
		if (!::SDL_JoystickGetAxisInitialState(joystick_, axis, &state)) {
			::SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Joystick AxisInitialState error [%s]", ::SDL_GetError());
			state = 0;
		}
		return state;
	}

	uint8_t getHat(int hat) const { return ::SDL_JoystickGetHat(joystick_, hat); }
	int getBall(int ball, int *dx, int *dy) const { return ::SDL_JoystickGetBall(joystick_, ball, dx, dy); }
	uint8_t getButton(int button) const { return ::SDL_JoystickGetButton(joystick_, button); }
	SDL_JoystickPowerLevel getCurrentPowerLevel() const { return ::SDL_JoystickCurrentPowerLevel(joystick_); }

	void updateJoyHatState(const SDL_JoyHatEvent &);
	void updateHoyButtonState(const SDL_JoyButtonEvent &);
	void updateState(uint32_t);

	bool isHatPress(int hat) const;
	bool isHatPressing(int hat) const;
	bool isHatPressTrigger(int hat) const;
	bool isHatReleaseTrigger(int hat) const;
	uint32_t getHatPressTick(int hat) const;
	void setHatPressTick(int hat, uint32_t tick);
	void setHatRepeatEnable(int hat, uint32_t delay, uint32_t interval);
	void setHatRepeatDisable(int hat);
	bool isHatRepeat(int hat) const;

	bool isLeftPress() const { return isHatPress(SDL_HAT_LEFT); }
	bool isLeftPressing() const { return isHatPressing(SDL_HAT_LEFT); }
	bool isLeftPressTrigger() const { return isHatPressTrigger(SDL_HAT_LEFT); }
	bool isLeftReleaseTrigger() const { return isHatReleaseTrigger(SDL_HAT_LEFT); }
	uint32_t getLeftPressTick() const { return getHatPressTick(SDL_HAT_LEFT); }
	void setLeftPressTick(uint32_t tick) { setHatPressTick(SDL_HAT_LEFT, tick); }
	void setLeftRepeatEnable(uint32_t delay, uint32_t interval) { setHatRepeatEnable(SDL_HAT_LEFT, delay, interval); }
	void setLeftRepeatDisable() { setHatRepeatDisable(SDL_HAT_LEFT); }
	bool isLeftRepeat() const { return isHatRepeat(SDL_HAT_LEFT); }

	bool isUpPress() const { return isHatPress(SDL_HAT_UP); }
	bool isUpPressing() const { return isHatPressing(SDL_HAT_UP); }
	bool isUpPressTrigger() const { return isHatPressTrigger(SDL_HAT_UP); }
	bool isUpReleaseTrigger() const { return isHatReleaseTrigger(SDL_HAT_UP); }
	uint32_t getUpPressTick() const { return getHatPressTick(SDL_HAT_UP); }
	void setUpPressTick(uint32_t tick) { setHatPressTick(SDL_HAT_UP, tick); }
	void setUpRepeatEnable(uint32_t delay, uint32_t interval) { setHatRepeatEnable(SDL_HAT_UP, delay, interval); }
	void setUpRepeatDisable() { setHatRepeatDisable(SDL_HAT_UP); }
	bool isUpRepeat() const { return isHatRepeat(SDL_HAT_UP); }

	bool isRightPress() const { return isHatPress(SDL_HAT_RIGHT); }
	bool isRightPressing() const { return isHatPressing(SDL_HAT_RIGHT); }
	bool isRightPressTrigger() const { return isHatPressTrigger(SDL_HAT_RIGHT); }
	bool isRightReleaseTrigger() const { return isHatReleaseTrigger(SDL_HAT_RIGHT); }
	uint32_t getRightPressTick() const { return getHatPressTick(SDL_HAT_RIGHT); }
	void setRightPressTick(uint32_t tick) { setHatPressTick(SDL_HAT_RIGHT, tick); }
	void setRightRepeatEnable(uint32_t delay, uint32_t interval) { setHatRepeatEnable(SDL_HAT_RIGHT, delay, interval); }
	void setRightRepeatDisable() { setHatRepeatDisable(SDL_HAT_RIGHT); }
	bool isRightRepeat() const { return isHatRepeat(SDL_HAT_RIGHT); }

	bool isDownPress() const { return isHatPress(SDL_HAT_DOWN); }
	bool isDownPressing() const { return isHatPressing(SDL_HAT_DOWN); }
	bool isDownPressTrigger() const { return isHatPressTrigger(SDL_HAT_DOWN); }
	bool isDownReleaseTrigger() const { return isHatReleaseTrigger(SDL_HAT_DOWN); }
	uint32_t getDownPressTick() const { return getHatPressTick(SDL_HAT_DOWN); }
	void setDownPressTick(uint32_t tick) { setHatPressTick(SDL_HAT_DOWN, tick); }
	void setDownRepeatEnable(uint32_t delay, uint32_t interval) { setHatRepeatEnable(SDL_HAT_DOWN, delay, interval); }
	void setDownRepeatDisable() { setHatRepeatDisable(SDL_HAT_DOWN); }
	bool isDownRepeat() const { return isHatRepeat(SDL_HAT_DOWN); }

	bool isButtonPress(int buttonIndex) const;
	bool isButtonPressing(int buttonIndex) const;
	bool isButtonPressTrigger(int buttonIndex) const;
	bool isButtonReleaseTrigger(int buttonIndex) const;
	uint32_t getButtonPressTick(int buttonIndex) const;
	void setButtonPressTick(int buttonIndex, uint32_t tick);
	void setButtonRepeatEnable(int buttonIndex, uint32_t delay, uint32_t interval);
	void setButtonRepeatDisable(int buttonIndex);

private:
	struct PressInfo
	{
		PressInfo()
			: tickPress()
			, repeatDelay()
			, repeatInterval()
			, repeatCount(-1)
			, prevPress()
			, currPress()
		{
		}
		uint32_t tickPress;
		uint32_t repeatDelay;
		uint32_t repeatInterval;
		int repeatCount;
		bool prevPress;
		bool currPress;
	};

	SDL_Joystick * const joystick_;
	std::unique_ptr<PressInfo[]> buttonPressInfoList_;
	std::map<int, PressInfo> hatPressInfoMap_;
	int numButtons_;
};

#endif // JOYSTICK_H_
