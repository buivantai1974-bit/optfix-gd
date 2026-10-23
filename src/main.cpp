#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(OptfixBaseLayer, GJBaseGameLayer) {
	CCParticleSystemQuad* createParticle(int p0, char const* p1, int p2, tCCPositionType p3) {
		auto particle = GJBaseGameLayer::createParticle(p0, p1, p2, p3);

		if (particle && Mod::get()->getSettingValue<bool>("enabled-particles")) {
			float scale = static_cast<float>(Mod::get()->getSettingValue<double>("particle-scale"));
			particle->setEmissionRate(particle->getEmissionRate() * scale);
		}
		return particle;
	}
};

class $modify(OptfixPlayLayer, PlayLayer) {
	void onQuit() {
		PlayLayer::onQuit();

		if (Mod::get()->getSettingValue<bool>("purge-on-exit")) {
			Loader::get()->queueInMainThread([] {
				CCTextureCache::sharedTextureCache()->removeUnusedTextures();
			});
		}
	}
};
