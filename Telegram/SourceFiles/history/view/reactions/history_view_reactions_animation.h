/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/effects/animations.h"

namespace Ui {
class AnimatedIcon;
} // namespace Lottie

namespace Ui::Text {
class CustomEmoji;
} // namespace Ui::Text

namespace Data {
class Reactions;
} // namespace Data

namespace HistoryView {
struct ReactionAnimationArgs;
} // namespace HistoryView

namespace HistoryView::Reactions {

class Animation final {
public:
	Animation(
		not_null<::Data::Reactions*> owner,
		ReactionAnimationArgs &&args,
		Fn<void()> repaint,
		int size);
	~Animation();

	void setRepaintCallback(Fn<void()> repaint);
	QRect paintGetArea(QPainter &p, QPoint origin, QRect target) const;

	[[nodiscard]] bool flying() const;
	[[nodiscard]] float64 flyingProgress() const;
	[[nodiscard]] bool finished() const;

private:
	[[nodiscard]] auto flyCallback();
	[[nodiscard]] auto callback();
	void startAnimations();
	int computeParabolicTop(int from, int to, float64 progress) const;
	void paintCenterFrame(QPainter &p, QRect target) const;

	const not_null<::Data::Reactions*> _owner;
	Fn<void()> _repaint;
	QImage _flyIcon;
	std::unique_ptr<Ui::Text::CustomEmoji> _custom;
	std::unique_ptr<Ui::AnimatedIcon> _center;
	std::unique_ptr<Ui::AnimatedIcon> _effect;
	Ui::Animations::Simple _fly;
	QRect _flyFrom;
	float64 _centerSizeMultiplier = 0.;
	bool _valid = false;

	mutable std::optional<int> _cachedKey;
	mutable float64 _cachedA = 0.;
	mutable float64 _cachedB = 0.;

};

} // namespace HistoryView::Reactions
