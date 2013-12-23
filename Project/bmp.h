class AUX_RGBImageRec {
	void convertBGRtoRGB();
public:
	byte *data;
	DWORD sizeX;
	DWORD sizeY;
	bool NoErrors;
	AUX_RGBImageRec() : NoErrors(false), data(NULL) {};
	AUX_RGBImageRec(const wchar_t *FileName);
	~AUX_RGBImageRec();
	bool loadFile(const wchar_t *FileName);
	friend AUX_RGBImageRec *auxDIBImageLoad(const wchar_t *FileName);
};
