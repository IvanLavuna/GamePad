//
// Created by ivan on 19.05.20.
//

#ifndef GAMEPAD_BURSTANIMATION_H
#define GAMEPAD_BURSTANIMATION_H
#include "Animation.h"

class BurstAnimation : public Animation
{
private:

public:
	BurstAnimation(float posX,float posY);
	~BurstAnimation() override;

//	void update() override ;
//	void render(sf::RenderTarget* target = nullptr) override;

};


#endif //GAMEPAD_BURSTANIMATION_H
