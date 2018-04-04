#include"DDS.h"

DDS_FILE* readDDS(const char* filename) {
	FILE* fp = NULL;
	DDS_FILE* DDS = NULL;

	errno_t errnno;
	int size;

	if ((errnno = fopen_s(&fp, filename, "rb")) != 0) {
		fprintf(stderr, "파일 열기 실패: file %s errno %d\n", filename, errnno);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);


	if ((DDS = (DDS_FILE*)new BYTE[size]) == NULL) {
		fprintf(stderr, "메모리를 할당 받지 못함\n");
		fclose(fp);
		return NULL;
	}
	fread(DDS, size, 1, fp);

	fclose(fp);

	return DDS;
}
DDS_FILE* readDDSRect(const char* filename, int x, int y, int width, int height) {
	
	FILE* fp = NULL;
	DDS_FILE* DDS = NULL;

	errno_t errno_d;
	int header_size;
	int total_size;

	//////파일 열기//////
	if ((errno_d = fopen_s(&fp, filename, "rb")) != 0) {

		fprintf(stderr, "파일 열기 실패:file %s errno %d\n", filename, errno_d);
		return NULL;
	}

	///////전체 파일이 아닌 읽어올 이미지 크기에 맞춰서 메모리 크기를 구함///////
	header_size = sizeof(DWORD) + sizeof(DDS_HEADER); //이미지 영역을 제외한 파일 헤더 크기
	total_size = header_size + width * height * 4;	  //읽어올 이미지 크기를 추가한 전체 크기

	//필요할 만큼 메모리를 할당 받는다. - 전체 파일 크기가 아닌.. 읽어올 이미지 크기와 헤더 크기만큼

	if ((DDS = (DDS_FILE*)new BYTE[total_size]) == NULL) {
		fprintf(stderr, "메모리를 할당 받지 못함\n");
		fclose(fp);		//전체 블록 읽기를 한다 - 바이너리 모드 읽기
		return NULL;
	}
	////////파일에 헤더만 읽어옴-이미지의 위치를 찾아서 특정 영역만 읽어와야 한다////////
	fread(DDS, header_size, 1, fp);

	////////파일에서 원하는 영역을 읽기 위한 변수 계산/////////
	int imgSize = width * height * 4;					//로드할 이미지 데이타 크기
	int lineSize = width * 4;							//로드할 이미지 한줄 데이타 크기
	int stride = DDS->header.dwPitchOrLinearSize;		//파일의 이미지 한줄 데이타 크기
	int offset = y * stride + x * 4;					//파일의 이미지 로드 시작 위치
	int lineGap = stride - lineSize;					//파일과 이미지 한줄 데이타 크기의 차

	fseek(fp, offset, SEEK_CUR);		//데이타 읽기 시작 위치로 이동

	for (int k = 0; k < height; k++) {
		fread(&DDS->data[k * width * 4], lineSize, 1, fp);	//파일에서 한줄을 읽는다.
		fseek(fp, lineGap, SEEK_CUR);						//파일에서 읽고 남은 줄을 건너뛰고.. 다음 읽을 위치로 이동한다.
	}

	/////실제 읽어온 이미지의 크기로.. 이미지 크기를 변경함/////
	DDS->header.dwHeight = height;
	DDS->header.dwWidth = width;

	/////파일 닫기/////
	fclose(fp);
	return DDS;
}