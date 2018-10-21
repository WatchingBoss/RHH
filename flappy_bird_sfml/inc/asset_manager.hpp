#ifndef MY_ASSET_MEMORY_HPP
#define MY_ASSET_MEMORY_HPP

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace Engine
{
class AssetManager {
  public:
	AssetManager( );
	~AssetManager( );

	void                LoadTexture( const std::string &, const std::string & );
	inline sf::Texture &GetTexture( const std::string &name ) { return m_Textures[name]; }

	void             LoadFont( const std::string &, const std::string & );
	inline sf::Font &GetFont( const std::string &name ) { return m_Fonts[name]; }

  private:
	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, sf::Font>    m_Fonts;
};
}  // namespace Engine

#endif
