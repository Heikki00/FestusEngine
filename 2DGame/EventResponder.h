#pragma once


class EventResponder : public GameComponent {
public:

	EventResponder();

	virtual void update() override;

	virtual MappedValues* save() override;

	virtual void load(const MappedValues& map) override;

	COMPONENTLOADCONSTRUCTOR(EventResponder)

};