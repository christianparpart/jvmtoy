#pragma once

class JObject;

struct JValue {
	uint32_t type;
	union {
		uint8_t Z;
		int16_t S;
		int32_t I;
		int64_t J;
		int16_t C;
		double D;
		float F;
		JObject* L;
	};
};

class JObject {
private:
	Class* type_;
	uint8_t* data_[];

public:
	JObject(Class* type);
	~JObject();

	JValue getField(uint16_t id);
	JValue getStatic(uint16_t id);
};
