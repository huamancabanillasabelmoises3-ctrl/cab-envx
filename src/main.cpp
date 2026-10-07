#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <iostream>
#include <cstdint>
#include <fstream>
#include <filesystem>

namespace bip = boost::interprocess;

using b8  = uint8_t;
using b16 = uint16_t;
using b32 = uint32_t;
using b64 = uint64_t;

int main() {
	try {
		const char* filename = "cabx-memory.bin";

		// 1. Crear el archivo y darle 8 bytes.
		{
			std::ofstream file(filename, std::ios::binary | std::ios::trunc);

			if (!file) {
				std::cerr << "No se pudo crear el archivo\n";
				return 1;
			}

			b64 zero = 0;
			file.write(
				reinterpret_cast<const char*>(&zero),
				sizeof(zero)
			);
		}

		// 2. Abrir el archivo mediante Boost.
		bip::file_mapping file(
			filename,
			bip::read_write
		);

		// 3. Mapearlo en memoria.
		bip::mapped_region region(
			file,
			bip::read_write
		);

		// 4. Obtener la dirección de la región.
		void* address = region.get_address();

		// 5. Interpretar los primeros 64 bits como b64.
		b64* value = static_cast<b64*>(address);

		// Escribir.
		*value = 0x123456789ABCDEF0ULL;

		std::cout << std::hex
			<< "Valor: " << *value << '\n';

		std::cout << std::dec
			<< "Bytes mapeados: "
			<< region.get_size()
			<< '\n';
	}
	catch (const bip::interprocess_exception& e) {
		std::cerr << "Boost: "
			<< e.what() << '\n';

		std::cerr << "Native error: "
			<< e.get_native_error()
			<< '\n';

		return 1;
	}
}