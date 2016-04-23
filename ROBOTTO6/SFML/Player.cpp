#include "Player.h"

Player::Player(void)
{
	loadFile("data/images/robotto.png");
	setAnimFrame(IntRect(24, 0, 48, 96));
	setPosition(Vector2f(1280/4,600));
	setCenter(Vector2f(24, 48));
	status = WAIT;
	isJumping = NO;


}


Player::~Player()
{
}

void Player::update(float delta, vector<Sprite*> object_list,RenderWindow &window)
{
	Event event;

	while (window.pollEvent(event)){
		if (event.type == Event::KeyReleased){
			if (event.key.code == Keyboard::Space && isJumping == NO){
				velocity.y -= jumpSpeed;
				isJumping = YES;
			}
			if (event.key.code == Keyboard::Right || event.key.code == Keyboard::Left){
				velocity.x = 0;
				status = WAIT;
			}
		}
		else if (event.type == Event::KeyPressed){
			if (event.key.code == Keyboard::Left){
				velocity.x = -moveSpeed;
				status = LEFT;
			}
			if (event.key.code == Keyboard::Right){
				velocity.x = moveSpeed;
				status = RIGHT;
			}
		}
		if (event.type == Event::Closed){
			window.close();
		}
	}
	

	if (checkIfCollision(object_list)){
		Sprite *object = getColidingObject();
		updateCollision(object);
	}
	else {
		Sprite *object = NULL;
		updateCollision(object);
	}


	
	if ((getPosition().y + getSize().height < actualHeight || velocity.y < 0)){
		isJumping = YES;
		if (velocity.y == 0) isFalling = true;
		velocity.y += gravity;

	} 
	else
	{
		isFalling = false;
		tempVelocityY = 0;
		isJumping = NO;

		setPosition(Vector2f(getPosition().x, actualHeight - getSize().height));
		velocity.y = 0;
	}

	move(Vector2f(velocity.x*delta, velocity.y*delta));
	
	
	if (anim_clock.getElapsedTime() > sf::seconds(0.09f))
	{
		if (isJumping == NO && status != WAIT){
			if (frame < 5)
			frame++;
			else frame = 0;
		}
		else if (isJumping == YES && status==WAIT){
			if (isFalling)
				frame = 1;
			else frame = 0;
		}
		else if (isJumping == YES && status != WAIT){
			if (isFalling)
				frame = 2;
			else frame = 1;
		}


		if (status == RIGHT && isJumping == NO){
			setAnimFrame(IntRect(frame * 96 + 24, 0, 48, 96));
		}
		else if (status == LEFT && isJumping == NO){
			setAnimFrame(IntRect(frame * 96 + 24, 96, 48, 96));
		}
		else if (status == WAIT && isJumping == NO){
			setAnimFrame(IntRect(24, 192, 48, 96));
		}
		else if (status == WAIT && isJumping == YES){
			setAnimFrame(IntRect(frame* 96 + 24, 288, 48, 96));
		}
		else if (status == RIGHT && isJumping == YES){
			setAnimFrame(IntRect(frame * 96 + 24, 384, 52, 96));
		}
		else if (status == LEFT && isJumping == YES){
			setAnimFrame(IntRect(frame * 96 + 20, 480, 52, 96));
		}
		anim_clock.restart();
	}
}

Vector2f Player::getVelocity(){
	return velocity;
}

void Player::stop()
{
	status = WAIT;
	frame = 0;
}


void Player::updateCollision(Sprite *object) {

	if (checkIfCollisionTop(object)){
		velocity.y = 0;
		if (checkIfCollisionLeft(object)){
			if (velocity.x > 0) {
				velocity.x = 0;
			}
			if ((getPosition().y + getSize().height < lastHeight)){
				tempVelocityY += gravity;
				velocity.y = tempVelocityY;
			}
			else {
				isFalling = false;
				tempVelocityY = 0;
				isJumping = NO;
	
				setPosition(Vector2f(getPosition().x, lastHeight - getSize().height));
				actualHeight = lastHeight;
				velocity.y = 0;

			}
		}
		else if (checkIfCollisionRight(object)){
			if (velocity.x < 0) {
				velocity.x = 0;
			}
			if ((getPosition().y + getSize().height < lastHeight)){
					tempVelocityY += gravity;
					velocity.y = tempVelocityY;
			}
			else {
				isFalling = false;
				tempVelocityY = 0;
				isJumping = NO;
	
				setPosition(Vector2f(getPosition().x, lastHeight - getSize().height));
				velocity.y = 0;
			}
		}
	}
	if (checkIfCollisionBottom(object)){
	
		actualHeight = getPosition().y + getSize().height;
		lastHeight = actualHeight;
	}
	else if (checkIfCollisionLeft(object)){
		if (velocity.x > 0){
			velocity.x = 0;
		}
	}
	else if (checkIfCollisionRight(object)){
		if (velocity.x < 0){
			velocity.x = 0;
		}
	}
	else {
		actualHeight = groundHeight;
	}
}

