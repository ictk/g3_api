
const unsigned char manage_pub[] = {
	0x72, 0xCF, 0x56, 0xF5, 0xBF, 0x87, 0x7D, 0xCF, 0x58, 0x23, 0x69, 0x16, 0x82, 0xE9, 0x82, 0x4C,
	0x0B, 0x97, 0x42, 0xD1, 0xE0, 0xB4, 0x1D, 0x28, 0x8B, 0x47, 0x8E, 0xCE, 0xF5, 0x21, 0x8B, 0xAA,
	0x1C, 0x48, 0x4C, 0xBB, 0x84, 0x8E, 0x44, 0x9A, 0x6A, 0x5B, 0xCD, 0x4A, 0x68, 0x6E, 0xCE, 0x67,
	0x62, 0x01, 0x07, 0x3F, 0xD6, 0x12, 0x41, 0x30, 0x2B, 0xEB, 0x18, 0x5C, 0x38, 0xE6, 0xE4, 0xBB,
};

const unsigned char manage_priv[] = {
	0x91, 0xF3, 0x3C, 0xD7, 0x31, 0x98, 0xE5, 0xCF, 0xD9, 0x64, 0xC2, 0x6B, 0x08, 0xFB, 0x3A, 0xB2,
	0x6A, 0x85, 0x5F, 0x32, 0xB0, 0x43, 0x5A, 0x2D, 0x0B, 0xA6, 0x93, 0xEF, 0xBB, 0xA1, 0x86, 0xED,
};

const unsigned char manage_hashed_msg[] = {
	0xE9, 0x59, 0x78, 0x7B, 0xF9, 0x36, 0x7A, 0x1C, 0xE9, 0x92, 0x66, 0xAF, 0xA1, 0x3C, 0xBA, 0xE5,
	0x3C, 0x4C, 0xE3, 0xDE, 0x08, 0x10, 0x46, 0x4D, 0x04, 0x77, 0xB6, 0x95, 0x52, 0x58, 0xF4, 0x82,
};

const unsigned char manage_sign_rs[] = {
	0xDB, 0x16, 0x6E, 0xC6, 0x1D, 0xCC, 0x61, 0x7F, 0xCC, 0x35, 0xF5, 0x41, 0x10, 0x81, 0xD3, 0x87,
	0x7E, 0x04, 0xE2, 0x96, 0x17, 0xD7, 0x7F, 0x0D, 0xCC, 0x21, 0x1D, 0x8D, 0x26, 0x3A, 0xA0, 0xD8,
	0x72, 0x89, 0x19, 0x2C, 0x3A, 0x48, 0x51, 0x06, 0x85, 0x3A, 0xD8, 0xB8, 0x88, 0x1E, 0x1C, 0xB3,
	0x4E, 0x18, 0x32, 0x0C, 0xD0, 0x75, 0xF7, 0xCA, 0xC3, 0x40, 0x34, 0x85, 0xFA, 0x48, 0x90, 0xCD,
};

const unsigned char server_pub[] = {
	0x14, 0x83, 0x29, 0x3F, 0x15, 0xB7, 0xEA, 0xCA, 0x54, 0x2B, 0x16, 0xFB, 0x5D, 0x76, 0xF4, 0x03,
	0x23, 0xE1, 0xF7, 0xE0, 0xAE, 0x29, 0x92, 0xAD, 0xF8, 0xB3, 0xC2, 0x31, 0x0E, 0x69, 0xBB, 0xEB,
	0x7A, 0x9F, 0x36, 0x57, 0x4E, 0x35, 0xEE, 0x26, 0x0B, 0x23, 0x21, 0x3A, 0xC0, 0x08, 0x2E, 0x70,
	0xAC, 0xB7, 0x57, 0xD8, 0x02, 0x7F, 0x69, 0x5D, 0x81, 0x05, 0x7C, 0x03, 0x49, 0x04, 0x0F, 0x55,
};

const unsigned char server_priv[] = {
	0x6F, 0x14, 0x02, 0x92, 0xD9, 0x5E, 0x99, 0x93, 0xCC, 0xFF, 0x1B, 0xB1, 0xA7, 0xA0, 0xE3, 0xE6,
	0x4F, 0xC0, 0x59, 0xDB, 0x14, 0x59, 0x55, 0x6A, 0x00, 0x1C, 0x00, 0xDA, 0xB6, 0x32, 0x52, 0x06,
};

const unsigned char server_hashed_msg[] = {
	0xF4, 0x68, 0x25, 0x26, 0x15, 0xD8, 0x04, 0x87, 0xDA, 0x21, 0x8D, 0xE2, 0x15, 0x09, 0x2F, 0x15,
	0x19, 0x8D, 0x1A, 0x61, 0xA2, 0xB0, 0xDC, 0x05, 0x7D, 0x20, 0x11, 0x2A, 0xEA, 0x6F, 0x08, 0xDA,
};

const unsigned char server_sign_rs[] = {
	0xC4, 0x78, 0x78, 0x2D, 0x42, 0x60, 0x4D, 0x06, 0x95, 0xE5, 0x86, 0x74, 0x93, 0x12, 0x99, 0x97,
	0x8C, 0x42, 0x56, 0xB6, 0x63, 0x33, 0x5D, 0x5C, 0x93, 0x83, 0x7E, 0xF0, 0x75, 0x41, 0x22, 0x94,
	0x0F, 0x41, 0x2A, 0x2D, 0x6C, 0x84, 0x28, 0x24, 0xD8, 0xD0, 0xC9, 0xE2, 0x29, 0xB0, 0x10, 0x1A,
	0x7D, 0x62, 0x1D, 0xCD, 0x0D, 0x30, 0xF7, 0x04, 0x13, 0xA9, 0x50, 0xD6, 0xCC, 0x06, 0xDD, 0x65,
};

const unsigned char pass_word[] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char sym_key[] = {
	0x91, 0xF3, 0x3C, 0xD7, 0x31, 0x98, 0xE5, 0xCF, 0xD9, 0x64, 0xC2, 0x6B, 0x08, 0xFB, 0x3A, 0xB2,
	0x6A, 0x85, 0x5F, 0x32, 0xB0, 0x43, 0x5A, 0x2D, 0x0B, 0xA6, 0x93, 0xEF, 0xBB, 0xA1, 0x86, 0xED,
};

const unsigned char cert[] = {
	0x30, 0x82, 0x01, 0xD2, 0x30, 0x82, 0x01, 0x77, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x09, 0x00, 0xBC, 0x13, 0x6E, 0x2C, 0xBE, 0xBD, 0x72, 0x97, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x30, 0x3A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x4B, 0x52, 0x31, 0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43, 0x54, 0x4B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x13, 0x49, 0x43, 0x54, 0x4B, 0x20, 0x53, 0x65, 0x6C, 0x66, 0x20, 0x53, 0x69, 0x67, 0x6E, 0x65, 0x64, 0x20, 0x43, 0x41, 0x30, 0x1E, 0x17, 0x0D, 0x31, 0x37, 0x31, 0x32, 0x31, 0x39, 0x30, 0x37, 0x30, 0x31, 0x31, 0x38, 0x5A, 0x17, 0x0D, 0x32, 0x32, 0x31, 0x32, 0x31, 0x38, 0x30, 0x37, 0x30, 0x31, 0x31, 0x38, 0x5A, 0x30, 0x46, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x4B, 0x52, 0x31, 0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43, 0x54, 0x4B, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x0C, 0x0C, 0x69, 0x63, 0x74, 0x6B, 0x20, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x08, 0x65, 0x63, 0x63, 0x20, 0x63, 0x65, 0x72, 0x74, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42, 0x00, 0x04, 0x09, 0xD6, 0x74, 0x9D, 0xC5, 0x5C, 0x0E, 0xF4, 0x36, 0x0E, 0x75, 0x81, 0x9D, 0xBD, 0x5D, 0xBB, 0xDD, 0x82, 0x5D, 0x39, 0xA0, 0xB5, 0x97, 0x8A, 0x11, 0x85, 0x5E, 0x16, 0x9B, 0x3E, 0x16, 0x49, 0x7A, 0x04, 0xF9, 0xD4, 0xCF, 0xCB, 0xE2, 0xE8, 0xB8, 0xEB, 0x53, 0x1F, 0x6C, 0x80, 0x9C, 0xC1, 0xEA, 0xE6, 0xAB, 0x23, 0x42, 0x20, 0x27, 0x80, 0x0D, 0xDC, 0xD5, 0x85, 0x5E, 0x94, 0xB3, 0xAE, 0xA3, 0x5A, 0x30, 0x58, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1D, 0x13, 0x04, 0x02, 0x30, 0x00, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x1E, 0x6D, 0x24, 0x91, 0x35, 0x9B, 0xC1, 0x23, 0xF8, 0xA0, 0xF2, 0xE2, 0x7C, 0x85, 0x06, 0xC6, 0xC3, 0x19, 0xB0, 0x4B, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04, 0x14, 0x90, 0x0F, 0xC9, 0xD4, 0x9F, 0x39, 0x79, 0xD8, 0xE7, 0x8D, 0x3E, 0xF1, 0xBB, 0x18, 0x24, 0x45, 0x76, 0x4D, 0x7E, 0x1C, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x1D, 0x0F, 0x04, 0x04, 0x03, 0x02, 0x05, 0xE0, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x03, 0x49, 0x00, 0x30, 0x46, 0x02, 0x21, 0x00, 0xA3, 0x63, 0x39, 0xD4, 0xDD, 0xB2, 0x70, 0x89, 0xD6, 0x5F, 0x91, 0xA4, 0x00, 0xC2, 0x71, 0xA1, 0x5A, 0x56, 0xAB, 0x89, 0x09, 0x98, 0x0E, 0xDC, 0x38, 0xE4, 0xCB, 0xC3, 0xF6, 0x6C, 0x10, 0x7F, 0x02, 0x21, 0x00, 0xAB, 0x99, 0x34, 0x56, 0x93, 0xDC, 0x4D, 0x1D, 0xC9, 0x81, 0x5F, 0xA8, 0x86, 0x15, 0xDE, 0x4A, 0xCB, 0x6A, 0x4D, 0x72, 0x41, 0x37, 0x19, 0x2E, 0xB5, 0x46, 0xDA, 0x4D, 0x6A, 0xD9, 0xC3, 0x32,

};

const unsigned char cert_wrong[] = {
	0x30, 0x82, 0x01, 0xD2, 0x30, 0x82, 0x01, 0x77, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x09, 0x00,
	0xBC, 0x13, 0x6E, 0x2C, 0xBE, 0xBD, 0x72, 0x97, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE,
	0x3D, 0x04, 0x03, 0x02, 0x30, 0x3A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
	0x02, 0x4B, 0x52, 0x31, 0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43,
	0x54, 0x4B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x13, 0x49, 0x43, 0x54,
	0x4B, 0x20, 0x53, 0x65, 0x6C, 0x66, 0x20, 0x53, 0x69, 0x67, 0x6E, 0x65, 0x64, 0x20, 0x43, 0x41,
	0x30, 0x1E, 0x17, 0x0D, 0x31, 0x37, 0x31, 0x32, 0x31, 0x39, 0x30, 0x37, 0x30, 0x31, 0x31, 0x38,
	0x5A, 0x17, 0x0D, 0x32, 0x32, 0x31, 0x32, 0x31, 0x38, 0x30, 0x37, 0x30, 0x31, 0x31, 0x38, 0x5A,
	0x30, 0x46, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x4B, 0x52, 0x31,
	0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43, 0x54, 0x4B, 0x31, 0x15,
	0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x0C, 0x0C, 0x69, 0x63, 0x74, 0x6B, 0x20, 0x50, 0x72,
	0x6F, 0x6A, 0x65, 0x63, 0x74, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x08,
	0x65, 0x63, 0x63, 0x20, 0x63, 0x65, 0x72, 0x74, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86,
	0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03,
	0x42, 0x00, 0x04, 0x09, 0xD6, 0x74, 0x9D, 0xC5, 0x5C, 0x0E, 0xF4, 0x36, 0x0E, 0x75, 0x81, 0x9D,
	0xBD, 0x5D, 0xBB, 0xDD, 0x82, 0x5D, 0x39, 0xA0, 0xB5, 0x97, 0x8A, 0x11, 0x85, 0x5E, 0x16, 0x9B,
	0x3E, 0x16, 0x49, 0x7A, 0x04, 0xF9, 0xD4, 0xCF, 0xCB, 0xE2, 0xE8, 0xB8, 0xEB, 0x53, 0x1F, 0x6C,
	0x80, 0x9C, 0xC1, 0xEA, 0xE6, 0xAB, 0x23, 0x42, 0x20, 0x27, 0x80, 0x0D, 0xDC, 0xD5, 0x85, 0x5E,
	0x94, 0xB3, 0xAE, 0xA3, 0x5A, 0x30, 0x58, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1D, 0x13, 0x04, 0x02,
	0x30, 0x00, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x1E,
	0x6D, 0x24, 0x91, 0x35, 0x9B, 0xC1, 0x23, 0xF8, 0xA0, 0xF2, 0xE2, 0x7C, 0x85, 0x06, 0xC6, 0xC3,
	0x19, 0xB0, 0x4B, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04, 0x14, 0x90, 0x0F,
	0xC9, 0xD4, 0x9F, 0x39, 0x79, 0xD8, 0xE7, 0x8D, 0x3E, 0xF1, 0xBB, 0x18, 0x24, 0x45, 0x76, 0x4D,
	0x7E, 0x1C, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x1D, 0x0F, 0x04, 0x04, 0x03, 0x02, 0x05, 0xE0, 0x30,
	0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x03, 0x49, 0x00, 0x30, 0x46,
	0x02, 0x21, 0x00, 0xA3, 0x63, 0x39, 0xD4, 0xDD, 0xB2, 0x70, 0x89, 0xD6, 0x5F, 0x91, 0xA4, 0x00,
	0xC2, 0x71, 0xA1, 0x5A, 0x56, 0xAB, 0x89, 0x09, 0x98, 0x0E, 0xDC, 0x38, 0xE4, 0xCB, 0xC3, 0xF6,
	0x6C, 0x10, 0x7F, 0x02, 0x21, 0x00, 0xAB, 0x99, 0x34, 0x56, 0x93, 0xDC, 0x4D, 0x1D, 0xC9, 0x81,
	0x5F, 0xA8, 0x86, 0x15, 0xDE, 0x4A, 0xCB, 0x6A, 0x4D, 0x72, 0x41, 0x37, 0x19, 0x2E, 0xB5, 0x46,
};

const unsigned char cert_pub_key[] = {
	0x09, 0xD6, 0x74, 0x9D, 0xC5, 0x5C, 0x0E, 0xF4, 0x36, 0x0E, 0x75, 0x81, 0x9D, 0xBD, 0x5D, 0xBB,
	0xDD, 0x82, 0x5D, 0x39, 0xA0, 0xB5, 0x97, 0x8A, 0x11, 0x85, 0x5E, 0x16, 0x9B, 0x3E, 0x16, 0x49,
	0x7A, 0x04, 0xF9, 0xD4, 0xCF, 0xCB, 0xE2, 0xE8, 0xB8, 0xEB, 0x53, 0x1F, 0x6C, 0x80, 0x9C, 0xC1,
	0xEA, 0xE6, 0xAB, 0x23, 0x42, 0x20, 0x27, 0x80, 0x0D, 0xDC, 0xD5, 0x85, 0x5E, 0x94, 0xB3, 0xAE,
};

const unsigned char cert_priv_key[] = {
	0xE6, 0x95, 0xFD, 0x8C, 0xEA, 0x8F, 0xE9, 0x12, 0x75, 0xB8, 0x73, 0x0C, 0x97, 0x73, 0x1A, 0x06,
	0x49, 0x5F, 0x8E, 0x4F, 0x9F, 0x8F, 0x5D, 0x37, 0x36, 0xE8, 0xAD, 0x40, 0xAC, 0x9C, 0x87, 0x5C,
};

const unsigned char outer_pub_key[] = {
	0x88, 0x17, 0xA5, 0x76, 0xA8, 0xB2, 0x07, 0x67, 0x07, 0x05, 0x71, 0x36, 0xA3, 0x62, 0xA8, 0x7B,
	0x96, 0xF9, 0xA2, 0x1F, 0x3D, 0xBF, 0x68, 0x64, 0xB3, 0xA7, 0xC0, 0x67, 0x05, 0xC9, 0x84, 0xFD,
	0xA3, 0x6E, 0xA8, 0x22, 0x73, 0x8F, 0xA1, 0xE4, 0x9E, 0x2A, 0x1E, 0x44, 0x93, 0xEA, 0x68, 0x1A,
	0x87, 0xCA, 0x02, 0xB1, 0x3B, 0x89, 0x63, 0x08, 0x0E, 0xA1, 0x71, 0x07, 0x0F, 0xEC, 0x3A, 0xF2,
};

const unsigned char outer_priv_key[] = {
	0x98, 0x62, 0xBB, 0x3D, 0xFA, 0xEF, 0x91, 0x8D, 0x7D, 0x75, 0x2E, 0x13, 0xAC, 0xB4, 0x76, 0x77,
	0x4F, 0x03, 0x12, 0x94, 0x7B, 0x78, 0x32, 0xEF, 0x36, 0x86, 0x5E, 0xA7, 0x45, 0x86, 0xB5, 0x68,
};

const unsigned char cert_without_sign[] = {
	0x30, 0x82, 0x01, 0xD2, 0x30, 0x82, 0x01, 0x77, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x09, 0x00,
	0xBC, 0x13, 0x6E, 0x2C, 0xBE, 0xBD, 0x72, 0x97, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE,
	0x3D, 0x04, 0x03, 0x02, 0x30, 0x3A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
	0x02, 0x4B, 0x52, 0x31, 0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43,
	0x54, 0x4B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x13, 0x49, 0x43, 0x54,
	0x4B, 0x20, 0x53, 0x65, 0x6C, 0x66, 0x20, 0x53, 0x69, 0x67, 0x6E, 0x65, 0x64, 0x20, 0x43, 0x41,
	0x30, 0x1E, 0x17, 0x0D, 0x31, 0x37, 0x31, 0x32, 0x31, 0x39, 0x30, 0x37, 0x30, 0x31, 0x31, 0x38,
	0x5A, 0x17, 0x0D, 0x32, 0x32, 0x31, 0x32, 0x31, 0x38, 0x30, 0x37, 0x30, 0x31, 0x31, 0x38, 0x5A,
	0x30, 0x46, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x4B, 0x52, 0x31,
	0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43, 0x54, 0x4B, 0x31, 0x15,
	0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x0C, 0x0C, 0x69, 0x63, 0x74, 0x6B, 0x20, 0x50, 0x72,
	0x6F, 0x6A, 0x65, 0x63, 0x74, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x08,
	0x65, 0x63, 0x63, 0x20, 0x63, 0x65, 0x72, 0x74, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86,
	0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03,
	0x42, 0x00, 0x04, 0x09, 0xD6, 0x74, 0x9D, 0xC5, 0x5C, 0x0E, 0xF4, 0x36, 0x0E, 0x75, 0x81, 0x9D,
	0xBD, 0x5D, 0xBB, 0xDD, 0x82, 0x5D, 0x39, 0xA0, 0xB5, 0x97, 0x8A, 0x11, 0x85, 0x5E, 0x16, 0x9B,
	0x3E, 0x16, 0x49, 0x7A, 0x04, 0xF9, 0xD4, 0xCF, 0xCB, 0xE2, 0xE8, 0xB8, 0xEB, 0x53, 0x1F, 0x6C,
	0x80, 0x9C, 0xC1, 0xEA, 0xE6, 0xAB, 0x23, 0x42, 0x20, 0x27, 0x80, 0x0D, 0xDC, 0xD5, 0x85, 0x5E,
	0x94, 0xB3, 0xAE, 0xA3, 0x5A, 0x30, 0x58, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1D, 0x13, 0x04, 0x02,
	0x30, 0x00, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x1E,
	0x6D, 0x24, 0x91, 0x35, 0x9B, 0xC1, 0x23, 0xF8, 0xA0, 0xF2, 0xE2, 0x7C, 0x85, 0x06, 0xC6, 0xC3,
	0x19, 0xB0, 0x4B, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04, 0x14, 0x90, 0x0F,
	0xC9, 0xD4, 0x9F, 0x39, 0x79, 0xD8, 0xE7, 0x8D, 0x3E, 0xF1, 0xBB, 0x18, 0x24, 0x45, 0x76, 0x4D,
	0x7E, 0x1C, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x1D, 0x0F, 0x04, 0x04, 0x03, 0x02, 0x05, 0xE0, 0x30,
};

const unsigned char G[] = {
	0x6B, 0x17, 0xD1, 0xF2, 0xE1, 0x2C, 0x42, 0x47, 0xF8, 0xBC, 0xE6, 0xE5, 0x63, 0xA4, 0x40, 0xF2,
	0x77, 0x03, 0x7D, 0x81, 0x2D, 0xEB, 0x33, 0xA0, 0xF4, 0xA1, 0x39, 0x45, 0xD8, 0x98, 0xC2, 0x96,
	0x4F, 0xE3, 0x42, 0xE2, 0xFE, 0x1A, 0x7F, 0x9B, 0x8E, 0xE7, 0xEB, 0x4A, 0x7C, 0x0F, 0x9E, 0x16,
	0x2B, 0xCE, 0x33, 0x57, 0x6B, 0x31, 0x5E, 0xCE, 0xCB, 0xB6, 0x40, 0x68, 0x37, 0xBF, 0x51, 0xF5,
};
const unsigned char passwd[] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


const unsigned char msg_org[] = {
	0x8D, 0x13, 0xA1, 0x71, 0xE5, 0x98, 0x14, 0x1F, 0x72, 0x19, 0x03, 0x62, 0x76, 0x68, 0x7E, 0x55, 0xD8, 0xED, 0xD3, 0x20, 0x76, 0xC1, 0x86, 0xA6, 0x89, 0xB1, 0x66, 0x50, 0x86, 0x5E, 0xA7, 0xA1, 0x19, 0xBF, 0x82, 0xA4, 0xCB, 0x9A, 0xF0, 0x0B, 0x94, 0xC6, 0xAE, 0xDF, 0xE5, 0x41, 0xEF, 0x81, 0x7C, 0x84, 0xB7, 0xC9, 0x99, 0x2C, 0xE9, 0xAE, 0x24, 0x0F, 0xDB, 0x44, 0x0F, 0xBF, 0x2D, 0xFB, 0xC9, 0x10, 0x26, 0xFE, 0x8B, 0x8F, 0xD2, 0xB4, 0x50, 0x24, 0x3B, 0x27, 0x88, 0x09, 0xE9, 0x13, 0xBD, 0xBF, 0x71, 0x24, 0xB8, 0x32, 0xAA, 0x5B, 0x66, 0xC3, 0x6F, 0x83, 0xA1, 0xB2, 0xA2, 0x60, 0xB6, 0x67, 0x76, 0x3F,
};
const unsigned char msg_from_sha256[] = {
	0x08, 0x5A, 0x19, 0x20, 0x1C, 0x9B, 0xB0, 0xBD, 0x59, 0x39, 0x7E, 0x20, 0x1F, 0xEF, 0x4A, 0x7E, 0x1B, 0xAD, 0x5D, 0x77, 0xBB, 0x88, 0xC5, 0xD1, 0xD1, 0xE3, 0x29, 0x2E, 0x01, 0x43, 0xA2, 0xE4,
};

const unsigned char iv[] = {
	0x17, 0x96, 0x34, 0x0C, 0x18, 0x10, 0x79, 0xD1, 0xEF, 0x55, 0x6E, 0xA2, 0xED, 0x1C, 0x8B, 0xF1,
};
const unsigned char plain[] = {
	0x1B, 0x39, 0xDD, 0x3E, 0x70, 0xCA, 0x61, 0x65, 0xB3, 0x97, 0x1A, 0xBC, 0xB6, 0x26, 0x2D, 0xAC, 0xA5, 0x26, 0xC9, 0x7E, 0x48, 0x45, 0x51, 0x5B, 0xE1, 0xD2, 0x6B, 0x4E, 0x24, 0x17, 0xE2, 0xEE, 0x72, 0xB6, 0x2A, 0x6A, 0x4E, 0xCD, 0xE6, 0x9B, 0x85, 0x20, 0x96, 0xC3, 0xE9, 0x31, 0x41, 0xAF,

};
const unsigned char cipher_aes_cbc[] = {
	0xEC, 0xC2, 0x56, 0x92, 0x04, 0x26, 0xB6, 0x8F, 0x0D, 0xDA, 0x31, 0x3D, 0x8E, 0xC9, 0x9E, 0x82, 0x4E, 0x49, 0xF3, 0x18, 0xA5, 0x63, 0xE0, 0xDB, 0x4B, 0xC9, 0xAB, 0x00, 0x4A, 0xF8, 0xBE, 0x95, 0x14, 0x6C, 0xE9, 0xC3, 0x9C, 0xA6, 0x80, 0xE5, 0x81, 0x59, 0x51, 0x1F, 0xA1, 0x3F, 0xC2, 0x6E,
};
const unsigned char server_ecdh_random[] = 
	{
		0x2A, 0x67, 0xC2, 0xB6, 0xA9, 0x50, 0x5B, 0x40, 0x19, 0xED, 0x11, 0x34, 0x8F, 0x72, 0xD4, 0x62, 0xF7, 0xF9, 0x84, 0x3E, 0xE9, 0x11, 0xF8, 0xA8, 0x7D, 0xDC, 0xE6, 0x75, 0xB1, 0xB0, 0xC0, 0xAE, 0xDE, 0xBA, 0x9F, 0x24, 0xA3, 0x61, 0xB6, 0x5C, 0x3D, 0xFE, 0x11, 0x75, 0x0A, 0x39, 0x43, 0x59, 0xD3, 0xA2, 0xA8, 0x1A, 0xA8, 0x33, 0x1F, 0x71, 0x2C, 0x41, 0x3A, 0xA9, 0x7C, 0x40, 0x2E, 0xAD,
	};
const unsigned char server_plain[] = {

	0x54, 0x4c, 0x53, 0x74, 0x65, 0x73, 0x74, 0x6d, 0x73, 0x67, 0x30, 0x31,
};
const unsigned char server_cipher[] = {
	0x63, 0xB1, 0xB2, 0x5A, 0x4A, 0x26, 0x4B, 0x3E, 0x1D, 0x71, 0xA5, 0xCB, 0xB4, 0x9D, 0xE0, 0xA6, 0x22, 0x52, 0xF9, 0x8F, 0x3A, 0x5D, 0x1D, 0xE9, 0xF5, 0x83, 0x04, 0x29, 0x00, 0x8C, 0xA1, 0xF8, 0x5B, 0x83, 0x59, 0x00, 0xEA, 0xBB, 0xBA, 0x71, 0x1F, 0x5D, 0x73, 0x44, 0xC0, 0x60, 0x8E, 0x9E, 0x66, 0xD5, 0x4E, 0x58, 0xAB, 0x1A, 0xD9, 0x27, 0x2B, 0xEC, 0x72, 0x8A, 0x25, 0x95, 0x51, 0x0C,
};
const unsigned char server_iv[] = {
	0xEC, 0x3C, 0x2D, 0x07, 0x93, 0x5F, 0x45, 0xFD, 0x5C, 0x74, 0x38, 0x57, 0x3F, 0x88, 0x72, 0xE7,
};
/*
다음과 같을 경우
c_mackey:CE2F86ECC0756071A09A22BF34CA5F3662A82FCA51A63036F5F7A87ACC07AA0C
s_mackey:482016790AA27EF55B92590229CFC1715B090C0C13587F22EE27793441A23870
c_key:10B9D3E424E6630F0565178DE026B5D3
s_key:521AF5A158690FD14FBA3A0A6ED77319
c_iv:02247A09E22F833332E23414CCBE68A2
s_iv:EC3C2D07935F45FD5C7438573F8872E7


*/


///////////////SIGN TEST/////////////////////////////



const unsigned char ext_pubkey[] = {
	0xB3, 0x3C, 0x5D, 0x9A, 0x6E, 0x05, 0xF2, 0x0C, 0x06, 0xF4, 0x31, 0x35, 0x8C, 0xAF, 0xE2, 0xC0, 0x62, 0x3B, 0x0E, 0xBE, 0x05, 0xA2, 0x07, 0x5D, 0xCB, 0x76, 0x06, 0x63, 0xAB, 0x69, 0x68, 0x2C, 0x4F, 0xBF, 0x17, 0x7F, 0x33, 0x91, 0xB6, 0x3F, 0x62, 0xFB, 0xE0, 0x69, 0x20, 0xF2, 0xFF, 0x80, 0xFE, 0x1F, 0x63, 0x06, 0x9C, 0x09, 0xF6, 0x20, 0x6F, 0xD8, 0xC5, 0x7C, 0x01, 0x3F, 0xF8, 0x0C,
};

const unsigned char ext_privkey[] = {
	0x11, 0x2E, 0xE0, 0xA7, 0x45, 0xEE, 0xC5, 0x60, 0x15, 0x53, 0x62, 0x47, 0x6E, 0x00, 0x2E, 0x88, 0x4D, 0x42, 0xF6, 0x7F, 0xE8, 0x6F, 0x3B, 0xB7, 0xFA, 0x6B, 0xDA, 0xAD, 0x32, 0xDE, 0x67, 0x38,
};

const unsigned char org_msg[] = {
	0x6B, 0x21, 0x77, 0xF5, 0x48, 0x33, 0x2D, 0x23, 0x34, 0x0C, 0x43, 0xD7, 0x3E, 0x36, 0x35, 0x62, 0x0B, 0x69, 0xA9, 0x34, 0x56, 0x3A, 0xBF, 0x07, 0xEA, 0xE5, 0x9E, 0x0F, 0x03, 0x4C, 0x13, 0x83, 0x82, 0x49, 0xC9, 0xB3, 0x1E, 0x71, 0x39, 0xB5, 0xE3, 0x45, 0x5C, 0xC6, 0x19, 0x05, 0xC8, 0x77, 0x76, 0xF1, 0x83, 0xF9, 0x9C, 0xE6, 0xFC, 0x68, 0x23, 0x18, 0xA5, 0x03, 0x70, 0x61, 0x70, 0xCF, 0xEF, 0x75, 0xEA, 0xE6, 0x62, 0x3D, 0xB4, 0xF3, 0x84, 0x66, 0xF5, 0x4E, 0x65, 0xD5, 0x0C, 0x92, 0x9B, 0xBF, 0xF2, 0x6B, 0x34, 0xF7, 0x9D, 0xD4, 0xD5, 0xED, 0x9E, 0xF2, 0x0F, 0x79, 0xCB, 0xD2, 0x3B, 0x78, 0x21, 0xF5, 0xCC, 0x6E, 0xE2, 0xE0, 0x9B, 0xA7, 0x4C, 0xCF, 0x6E, 0x12, 0x23, 0x4A, 0x8C, 0xC5, 0xA9, 0x4A, 0xEF, 0x46, 0x49, 0x39, 0x3C, 0xC9, 0x29, 0x7F, 0x47, 0x7A, 0xF3, 0xC7, 0x09, 0xF6, 0xFF, 0x10, 0x43, 0xDE, 0x94, 0xD0, 0x9E, 0xFE, 0x08, 0x56, 0x3A, 0x30, 0xCF, 0x61, 0xCF, 0x7B, 0xEC, 0xF9, 0xAD, 0x5A, 0x7C, 0x00, 0xBA, 0x02, 0xDC, 0x95, 0xAB, 0x0D, 0x2D, 0xF5, 0x9E, 0x59, 0x7E, 0xB6, 0xD8, 0x7B, 0xBD, 0x5C, 0xE6, 0xEE, 0xB8, 0x8A, 0x6F, 0xC9, 0x14, 0xE1,
};

const unsigned char org_msg_hash[] = {
	0xB4, 0x9B, 0x64, 0xA5, 0x01, 0x51, 0xDB, 0x4F, 0xD6, 0x81, 0x0E, 0xA0, 0xFE, 0x99, 0x08, 0x1C, 0xB2, 0x13, 0x0B, 0xEC, 0xDD, 0xC2, 0x96, 0x96, 0xF6, 0x44, 0xC6, 0x18, 0x18, 0xAC, 0x11, 0x64,
};

const unsigned char sign_rs[] = {
	0xF7, 0x93, 0x5B, 0xC4, 0x44, 0x19, 0xA3, 0xF2, 0x10, 0x17, 0x78, 0x1F, 0x5A, 0xD4, 0x8E, 0xB3, 0xCA, 0x8F, 0x7D, 0xD9, 0x2E, 0x9D, 0x0B, 0x71, 0xB6, 0xBB, 0xCF, 0x58, 0xE7, 0x85, 0x04, 0x73, 0x28, 0x8A, 0x2B, 0x23, 0x41, 0x72, 0x74, 0x28, 0x0D, 0x85, 0x05, 0x51, 0x81, 0x20, 0xD1, 0x0A, 0xBC, 0x65, 0x1C, 0x2E, 0xFB, 0x3E, 0xAD, 0x0C, 0xAB, 0x4A, 0x6A, 0x97, 0x93, 0xD5, 0x5D, 0xB5,
};

//const unsigned char cert[] =  { 0x30, 0x82, 0x01, 0x64, 0x30, 0x82, 0x01, 0x0A, 0x02, 0x09, 0x00, 0xE7, 0x38, 0x25, 0x93, 0x6D, 0xDE, 0x66, 0x5A, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x30, 0x3A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x4B, 0x52, 0x31, 0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43, 0x54, 0x4B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x13, 0x49, 0x43, 0x54, 0x4B, 0x20, 0x53, 0x65, 0x6C, 0x66, 0x20, 0x53, 0x69, 0x67, 0x6E, 0x65, 0x64, 0x20, 0x43, 0x41, 0x30, 0x1E, 0x17, 0x0D, 0x31, 0x37, 0x31, 0x31, 0x31, 0x37, 0x30, 0x37, 0x35, 0x33, 0x34, 0x34, 0x5A, 0x17, 0x0D, 0x32, 0x37, 0x31, 0x31, 0x31, 0x35, 0x30, 0x37, 0x35, 0x33, 0x34, 0x34, 0x5A, 0x30, 0x3A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x4B, 0x52, 0x31, 0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x04, 0x49, 0x43, 0x54, 0x4B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x13, 0x49, 0x43, 0x54, 0x4B, 0x20, 0x53, 0x65, 0x6C, 0x66, 0x20, 0x53, 0x69, 0x67, 0x6E, 0x65, 0x64, 0x20, 0x43, 0x41, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42, 0x00, 0x04, 0xD5, 0x7C, 0xBA, 0xB7, 0x68, 0x2A, 0xE9, 0x76, 0x81, 0xC7, 0x2F, 0xAB, 0x34, 0xAF, 0x28, 0x73, 0xCD, 0xBB, 0x49, 0xE4, 0x42, 0xF8, 0x5E, 0xFE, 0xA4, 0xDE, 0x55, 0xC5, 0x1E, 0xD0, 0x93, 0xEE, 0x7E, 0x1A, 0xD8, 0xC3, 0xE4, 0x02, 0x5E, 0x80, 0xF9, 0xC4, 0xF8, 0x66, 0xB2, 0x60, 0x00, 0xD5, 0xC8, 0xE3, 0x1C, 0x83, 0x80, 0x70, 0xD9, 0xC0, 0xA1, 0x8F, 0xF7, 0x5A, 0xA0, 0xEC, 0x9B, 0x4B, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x20, 0x4D, 0x36, 0xCE, 0x61, 0x51, 0x66, 0x91, 0x75, 0x02, 0x19, 0x28, 0x5E, 0xDF, 0x5E, 0x85, 0x2E, 0x6D, 0x4E, 0x44, 0xA2, 0x00, 0x26, 0x75, 0x80, 0xD4, 0xA6, 0xFB, 0x40, 0xD5, 0x23, 0x8F, 0xA3, 0x02, 0x21, 0x00, 0xC2, 0x54, 0x63, 0x68, 0x9E, 0x4B, 0x08, 0x9C, 0x97, 0xF9, 0x06, 0xB1, 0x9B, 0x18, 0xC2, 0x47, 0x84, 0x92, 0x41, 0xEE, 0xDB, 0xD9, 0x99, 0x24, 0xE2, 0xC6, 0x5C, 0x7A, 0x7D, 0x61, 0x30, 0xC9, };