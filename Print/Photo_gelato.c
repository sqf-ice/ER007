#include "TypeDef.h"

CONST struct GRAPH_DEFINE graph_info_gelato = {
		/*.cGrapCols =*/ 6,
		/*.cLabels =*/ 5,
		/*.cPrintAt =*/ 0,
		/*.cWidthAChar */ 12,
		/*.cHighAChar */ 32,
		/*.cByteALine =*/ 24,
		/*.cGrapSize =*/ 1565,
};

CONST BYTE photo_data_gelato[] = {
"Very Good               \x0a"\
"Very Good               \x00"\
"Very Good               \x00"\
"Very Good               \x00"\
"Very Good               \x00"\
//Bytes:1440
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x03\xFC\x00\x00\x00\x00"\
"\x00\x00\x00\x1F\xFE\x00\x00\x00\x00"\
"\x00\x00\x00\x3F\xFF\x00\x00\x00\x00"\
"\x00\x00\x00\x3F\xF7\x80\x00\x00\x00"\
"\x00\x00\x00\x7F\xFF\x80\x06\x00\x00"\
"\x00\x00\x00\x7F\xFF\x80\x0F\xE0\x00"\
"\x00\x00\x00\x7F\xFF\x80\x1F\xF0\x00"\
"\x00\x00\x00\x7F\xFF\xC0\x3F\xF8\x00"\
"\x00\x00\x00\x7F\xFF\xC0\x3F\xFC\x00"\
"\x00\x00\x00\x7F\xFF\x80\x7F\xFC\x00"\
"\x00\x00\x00\x7F\xFF\x80\x7F\xFE\x00"\
"\x00\x00\x00\x3F\xFF\x80\xFF\xFE\x00"\
"\x00\x00\x00\x3F\xFF\x01\xFF\xFE\x00"\
"\x00\x00\x00\x27\xFD\x81\xFF\xFE\x00"\
"\x00\x00\x00\x62\x31\x83\xFF\xFE\x00"\
"\x00\x00\x00\x40\x31\x83\xFF\xFC\x00"\
"\x00\x00\x00\xC0\x30\x87\xFF\xF8\x00"\
"\x00\x00\x00\x8C\x00\xC7\xFF\xF8\x00"\
"\x00\x00\x01\x88\x00\x4F\xFF\xF0\x00"\
"\x00\x00\x02\x18\x00\x7F\xFF\xE0\x00"\
"\x00\x00\x0C\x10\x00\x5F\xFF\xC0\x00"\
"\x00\x00\x18\x20\x00\xCF\xFF\xC0\x00"\
"\x00\x00\x30\x00\x80\x8F\xFF\x80\x00"\
"\x00\x00\x20\x00\x80\x0F\xFF\x80\x00"\
"\x00\x00\x68\x00\x80\x0F\xFF\x00\x00"\
"\x00\x00\x48\x01\x00\x0F\xFE\x00\x00"\
"\x00\x00\x58\x03\x00\x0F\xFE\x00\x00"\
"\x00\x00\x50\x06\x00\x09\xFE\x00\x00"\
"\x00\x00\x60\x0C\x00\x09\xFB\x00\x00"\
"\x00\x00\xC0\x38\x00\x08\x39\x00\x00"\
"\x00\x01\x80\xE0\x00\x08\x12\x00\x00"\
"\x00\x03\x01\x80\x00\x10\x06\x00\x00"\
"\x00\x04\x03\x00\x40\x10\x07\x00\x00"\
"\x00\x18\x0C\x00\xC0\x30\x05\x00\x00"\
"\x00\x30\x18\x00\x80\x00\x0C\x80\x00"\
"\x00\x60\x00\x01\x80\x00\x0C\x80\x00"\
"\x00\xC0\x00\x03\x00\x00\x08\x80\x00"\
"\x00\x80\x00\x0E\x00\x00\x08\x80\x00"\
"\x01\x00\x00\x38\x00\x20\x10\x80\x00"\
"\x03\x00\x01\xE0\x00\x20\x00\x80\x00"\
"\x02\x00\x03\x00\x00\x40\x00\x80\x00"\
"\x02\x00\x06\x00\x01\xC0\x00\x80\x00"\
"\x02\x00\x04\x00\x07\x00\x01\x80\x00"\
"\x02\x00\x04\x00\x1C\x00\x41\x80\x00"\
"\x02\x20\x00\x00\x30\x00\xC3\x80\x00"\
"\x02\x60\x00\x00\x60\x00\x86\xC0\x00"\
"\x02\x60\x00\x00\x40\x01\x84\xC0\x00"\
"\x00\x40\x00\x00\x42\x21\x80\xC0\x00"\
"\x03\x40\x08\x00\x03\x31\x80\xC0\x00"\
"\x03\xE1\x1F\xFF\xFF\x11\xFF\xC0\x00"\
"\x02\x23\x18\x00\x03\x30\x80\x40\x00"\
"\x02\x32\x18\x00\x03\x20\x80\x40\x00"\
"\x01\x32\x18\x00\x01\xE0\xC0\xC0\x00"\
"\x01\xF2\x1F\xFF\xFF\xE0\xFF\x80\x00"\
"\x00\x33\x30\x00\x00\x20\x8C\x00\x00"\
"\x00\x21\xE0\x00\x00\x20\x98\x00\x00"\
"\x00\x20\x80\x00\x00\x21\x30\x00\x00"\
"\x00\x21\x80\x00\x00\x1B\x60\x00\x00"\
"\x00\x21\x80\x00\x00\x00\x40\x00\x00"\
"\x00\x3E\x80\x00\x00\x00\x80\x00\x00"\
"\x00\x0C\xFF\xFF\xFF\xFF\x80\x00\x00"\
"\x00\x03\x00\x00\x00\x00\x40\x00\x00"\
"\x00\x01\x00\x00\x00\x00\x40\x00\x00"\
"\x00\x01\x80\x00\x00\x00\xC0\x00\x00"\
"\x00\x00\xFF\xFF\xFF\xFF\x80\x00\x00"\
"\x00\x00\x40\x00\x00\x03\x00\x00\x00"\
"\x00\x00\x40\x00\x00\x02\x00\x00\x00"\
"\x00\x00\x40\x00\x00\x02\x00\x00\x00"\
"\x00\x00\x40\x00\x00\x02\x00\x00\x00"\
"\x00\x00\x60\x00\x00\x02\x00\x00\x00"\
"\x00\x00\x60\x00\x00\x06\x00\x00\x00"\
"\x00\x00\x20\x00\x00\x06\x00\x00\x00"\
"\x00\x00\x2F\xFF\xFF\xFC\x00\x00\x00"\
"\x00\x00\x60\x00\x00\x06\x00\x00\x00"\
"\x00\x00\xC0\x00\x00\x02\x00\x00\x00"\
"\x00\x00\xC0\x00\x00\x02\x00\x00\x00"\
"\x00\x00\x7F\xFF\xFF\xFC\x00\x00\x00"\
"\x00\x00\x1F\xFF\xFD\xFC\x00\x00\x00"\
"\x00\x00\x10\xE0\x1C\x18\x00\x00\x00"\
"\x00\x00\x10\x70\x32\x38\x00\x00\x00"\
"\x00\x00\x10\xD8\x21\x38\x00\x00\x00"\
"\x00\x00\x10\x8C\x40\xC8\x00\x00\x00"\
"\x00\x00\x19\x03\x80\xD0\x00\x00\x00"\
"\x00\x00\x1F\x01\x81\xB0\x00\x00\x00"\
"\x00\x00\x07\x03\x43\x10\x00\x00\x00"\
"\x00\x00\x0D\x86\x32\x10\x00\x00\x00"\
"\x00\x00\x08\x44\x14\x10\x00\x00\x00"\
"\x00\x00\x08\x38\x0C\x10\x00\x00\x00"\
"\x00\x00\x08\x10\x1E\x30\x00\x00\x00"\
"\x00\x00\x0C\x3C\x11\x30\x00\x00\x00"\
"\x00\x00\x0C\x66\x20\xE0\x00\x00\x00"\
"\x00\x00\x0C\x43\x60\xE0\x00\x00\x00"\
"\x00\x00\x04\x81\xC0\xA0\x00\x00\x00"\
"\x00\x00\x07\x00\xC1\xA0\x00\x00\x00"\
"\x00\x00\x07\x81\xE3\x20\x00\x00\x00"\
"\x00\x00\x06\x63\x32\x40\x00\x00\x00"\
"\x00\x00\x06\x36\x1C\x40\x00\x00\x00"\
"\x00\x00\x06\x0C\x0C\x40\x00\x00\x00"\
"\x00\x00\x06\x0C\x1E\x40\x00\x00\x00"\
"\x00\x00\x02\x1B\x32\x40\x00\x00\x00"\
"\x00\x00\x02\x11\xA1\xC0\x00\x00\x00"\
"\x00\x00\x03\x20\xE1\xC0\x00\x00\x00"\
"\x00\x00\x03\xC0\xE1\x80\x00\x00\x00"\
"\x00\x00\x03\xC0\xB2\x80\x00\x00\x00"\
"\x00\x00\x03\xA1\x1E\x80\x00\x00\x00"\
"\x00\x00\x03\x1B\x0C\x80\x00\x00\x00"\
"\x00\x00\x01\x0E\x0E\x80\x00\x00\x00"\
"\x00\x00\x01\x0E\x11\x80\x00\x00\x00"\
"\x00\x00\x01\x0F\x11\x00\x00\x00\x00"\
"\x00\x00\x01\x19\xA1\x00\x00\x00\x00"\
"\x00\x00\x01\x90\xC3\x00\x00\x00\x00"\
"\x00\x00\x01\xE0\x67\x00\x00\x00\x00"\
"\x00\x00\x00\xE0\xBD\x00\x00\x00\x00"\
"\x00\x00\x00\xF1\x1B\x00\x00\x00\x00"\
"\x00\x00\x00\x9B\x1F\x00\x00\x00\x00"\
"\x00\x00\x00\x86\x33\x00\x00\x00\x00"\
"\x00\x00\x00\xFF\xFE\x00\x00\x00\x00"\
"\x00\x00\x01\x00\x01\x00\x00\x00\x00"\
"\x00\x00\x01\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x80\x03\x00\x00\x00\x00"\
"\x00\x00\x00\xFF\xFE\x00\x00\x00\x00"\
"\x00\x00\x00\x40\x04\x00\x00\x00\x00"\
"\x00\x00\x00\x40\x04\x00\x00\x00\x00"\
"\x00\x00\x00\x60\x04\x00\x00\x00\x00"\
"\x00\x00\x00\x20\x0C\x00\x00\x00\x00"\
"\x00\x00\x00\x20\x08\x00\x00\x00\x00"\
"\x00\x00\x00\x30\x08\x00\x00\x00\x00"\
"\x00\x00\x00\x30\x08\x00\x00\x00\x00"\
"\x00\x00\x00\x10\x18\x00\x00\x00\x00"\
"\x00\x00\x00\x10\x10\x00\x00\x00\x00"\
"\x00\x00\x00\x18\x30\x00\x00\x00\x00"\
"\x00\x00\x00\x08\x20\x00\x00\x00\x00"\
"\x00\x00\x00\x08\x60\x00\x00\x00\x00"\
"\x00\x00\x00\x07\xC0\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"\
"\x00\x00\x00\x00\x00\x00\x00\x00\x00"

};
