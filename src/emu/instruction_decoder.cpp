#include "emu/instruction_decoder.hpp"
#include "util/bits.hpp"
#include <bitset>

namespace momo {

InstructionIndex find_instruction_index(std::string_view name)
{
    InstructionIndex index = 0;
    for (const auto& ienc : InstructionEncodings)
    {
        if (name == ienc.name)
            return index;

        ++index;
    }

    MOMO_ASSERT(false, "Instruction index not found");
    return 0xFF;
}

InstructionIndex InstructionDecoder::decode(Instruction ins)
{
    for (InstructionIndex index = 0; index < static_cast<InstructionIndex>(InstructionEncodings.size()); ++index)
    {
        const auto& ienc = InstructionEncodings[index];
        bool passed_all_components = true;

        for (u8 x = 0; x < ienc.num_components; ++x)
        {
            const auto& br = ienc.bit_targets[x];
            const auto& target = ienc.targets[x];

            u16 bits = toggle_bit_range(br.start, br.end);

            u16 ins_mask = ins & bits;
            ins_mask >>= br.start - 1;

            if (ins_mask != target)
            {
                passed_all_components = false;
                break;
            }
        }

        if (passed_all_components)
            return index;
    }

    MOMO_ASSERT(false, "Failed to decode instruction");
    return 0;
}

} // namespace momo