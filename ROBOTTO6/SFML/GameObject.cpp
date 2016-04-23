#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

bool GameObject::loadFile(String path){
	if (!texture.loadFromFile(path)){
		return false;
	}
	else{
		sprite.setTexture(texture);
		return true;
	}

}
void GameObject::loadFromTexture(Texture texture){

		sprite.setTexture(texture);

}

void GameObject::setAnimFrame(IntRect &rect){
	sprite.setTextureRect(rect);
}

void GameObject::setPosition(Vector2f position) {
	sprite.setPosition(position);
}

Vector2f GameObject::getPosition(){
	return sprite.getPosition();
}

FloatRect GameObject::getSize(){
	return sprite.getGlobalBounds();
}

Vector2f GameObject::getCenter(){
	return sprite.getOrigin();
}

void GameObject::setCenter(Vector2f position){
	sprite.setOrigin(position);
}

void GameObject::draw(RenderTarget &target,RenderStates states) const {
	target.draw(sprite,states);
}
void GameObject::move(Vector2f destination){
	sprite.move(destination);
}

FloatRect GameObject::getGlobalBounds() {
	return sprite.getGlobalBounds();
}

Sprite GameObject::getSprite(){
	return sprite;
}