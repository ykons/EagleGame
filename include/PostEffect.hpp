#ifndef POSTEFFECT_HPP
#define POSTEFFECT_HPP

namespace sf
{
	class RenderTarget;
	class RenderTexture;
	class Shader;
}

class PostEffect
{
public:
	virtual ~PostEffect();
	virtual void apply(const sf::RenderTexture &input, sf::RenderTarget &output) = 0;

	static bool isSupported();

protected:
	static void applyShader(const sf::Shader &shader, sf::RenderTarget &output);
};

#endif // POSTEFFECT_HPP
