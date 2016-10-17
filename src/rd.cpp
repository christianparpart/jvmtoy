#include <stdio.h>
#include <deque>
#include <vector>

class Classfile {
public:
	const char* filename;
	uint32_t flags; // ACC_PUBLIC, ACC_SUPER, ...
	int minor;
	int major;

	ConstantPool* constants;
	Method* methods;

	Classfile(const char* classfile);
	~Classfile();
};

class Frame {
private:
	uint8_t* program_;  //!< program opcode stream
	uint8_t* local_;    //!< vector of local variables
	uint8_t* stack_;    //!< local stack

	size_t ip_;
	size_t sp_;

public:
	Frame(const Frame&) = delete;
	Frame&& operator=(Frame& v) = delete;

	Frame(size_t nlocals, size_t stack, uint8_t* program);
	~Frame();

	Frame(Frame&& v);
	Frame&& operator=(Frame&& v);

	void run();

private:
	// program processing
	uint8_t read8() { return program_[ip_++]; }
	uint16_t read16() { return read8() << 8 | read8(); }
	uint32_t read32() { return read16() << 16 | read16(); }

	// stack management
	int pop() { return stack_[sp_--]; }
	void push(int value) { stack_[sp++] = value; }
};

class Heap {
};

class ExecutionEngine {
private:
	std::deque<Frame*> frameStack;

public:
	ExecutionEngine();
	~ExecutionEngine();

	void setProgram(const Frame* frame);

	void run();

	inline void nop();
	inline void aconst_null();
	inline void iconst_m1();
	inline void iconst_0();
};

// {{{ Frame impl
void ExecutionEngine::run()
{
	static const void (ExecutionEngine::*ops()) = {
		[0x00] = &nop,
		[0x01] = &aconst_null,
		[0x02] = &iconst_m1,
		[0x03] = &iconst_0,
	};

	while (true) {
		uint8_t instr = read8();
		ops[instr]();
	}
}

void ExecutionEngine::iconst_0() {
	opstack[sp++] = 0;
}

void ExecutionEngine::run()
{
	sp_ = 0;
	int itmp = 0;

	switch (read8()) {
		case 0x15: // iload(): val
			stack_[sp_++] = local_[read8()];
			break;
		case 0x1a: // iload_0(): val
			stack_[sp_++] = local_[0];
			break;
		case 0x1b: // iload_1(): val
			stack_[sp_++] = local_[1];
			break;
		case 0x1c: // iload_2(): val
			stack_[sp_++] = local_[2];
			break;
		case 0x1d: // iload_3(): val
			stack_[sp_++] = local_[3];
			break;
		case 0x36: // istore(): val
			local_[read8()] = stack_pop();
			break;
		case 0x3b: // istore_0(): val
			local_[0] = stack_[--sp_];
			break;
		case 0x3c: // istore_1(): val
			local_[1] = stack_[--sp_];
			break;
		case 0x3d: // istore_2(): val
			local_[2] = stack_[--sp_];
			break;
		case 0x3e: // istore_3(): val
			local_[3] = stack_[--sp_];
			break;
		case 0x64: { // isub(val, val): val
			auto a = pop();
			auto b = pop();
			push(a - b);
			break;
		}
		case 0x7c: { // iushr(val, val): val
			auto a = pop();
			auto b = pop();
			push(b >> a);
			break;
		}
		case 0x70: { // irem(val, val): val
			itmp = stack_[sp_ - 1] % stack_[sp_ - 2];
			sp_ -= 2;
			stack_[sp_++] = itmp;
			break;
		}
		case 0x9f: { // if_icmpeq(val, val): val
			int16_t jmp = ip_ + read16() - 1;
			auto a = pop();
			auto b = pop();
			if (a == b)
				ip_ = jmp;
			break;
		}
		default:
			break;
	}
}
// }}}

int main() {
}
