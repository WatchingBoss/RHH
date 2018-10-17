#include "../inc/asset_manager.hpp"
#include <iostream>

namespace Engine
{
AssetManager::AssetManager( ) : m_Textures( ), m_Fonts( ) {}
AssetManager::~AssetManager( ) {}

void AssetManager::LoadTexture( const std::string &name, const std::string &file_path ) {
	sf::Texture texture;

	if ( !texture.loadFromFile( file_path ) )
		std::cout << "Cannot load file: " << file_path << std::endl;
	m_Textures[name] = texture;
}

void AssetManager::LoadFont( const std::string &name, const std::string &file_path ) {
	sf::Font font;

	if ( !font.loadFromFile( file_path ) )
		std::cout << "Cannot load file: " << file_path << std::endl;
	m_Fonts[name] = font;
}

}  // namespace Engine
