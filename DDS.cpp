#include"DDS.h"

DDS_FILE* readDDS(const char* filename) {
	FILE* fp = NULL;
	DDS_FILE* DDS = NULL;

	errno_t errnno;
	int size;

	if ((errnno = fopen_s(&fp, filename, "rb")) != 0) {
		fprintf(stderr, "���� ���� ����: file %s errno %d\n", filename, errnno);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);


	if ((DDS = (DDS_FILE*)new BYTE[size]) == NULL) {
		fprintf(stderr, "�޸𸮸� �Ҵ� ���� ����\n");
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

	//////���� ����//////
	if ((errno_d = fopen_s(&fp, filename, "rb")) != 0) {

		fprintf(stderr, "���� ���� ����:file %s errno %d\n", filename, errno_d);
		return NULL;
	}

	///////��ü ������ �ƴ� �о�� �̹��� ũ�⿡ ���缭 �޸� ũ�⸦ ����///////
	header_size = sizeof(DWORD) + sizeof(DDS_HEADER); //�̹��� ������ ������ ���� ��� ũ��
	total_size = header_size + width * height * 4;	  //�о�� �̹��� ũ�⸦ �߰��� ��ü ũ��

	//�ʿ��� ��ŭ �޸𸮸� �Ҵ� �޴´�. - ��ü ���� ũ�Ⱑ �ƴ�.. �о�� �̹��� ũ��� ��� ũ�⸸ŭ

	if ((DDS = (DDS_FILE*)new BYTE[total_size]) == NULL) {
		fprintf(stderr, "�޸𸮸� �Ҵ� ���� ����\n");
		fclose(fp);		//��ü ��� �б⸦ �Ѵ� - ���̳ʸ� ��� �б�
		return NULL;
	}
	////////���Ͽ� ����� �о��-�̹����� ��ġ�� ã�Ƽ� Ư�� ������ �о�;� �Ѵ�////////
	fread(DDS, header_size, 1, fp);

	////////���Ͽ��� ���ϴ� ������ �б� ���� ���� ���/////////
	int imgSize = width * height * 4;					//�ε��� �̹��� ����Ÿ ũ��
	int lineSize = width * 4;							//�ε��� �̹��� ���� ����Ÿ ũ��
	int stride = DDS->header.dwPitchOrLinearSize;		//������ �̹��� ���� ����Ÿ ũ��
	int offset = y * stride + x * 4;					//������ �̹��� �ε� ���� ��ġ
	int lineGap = stride - lineSize;					//���ϰ� �̹��� ���� ����Ÿ ũ���� ��

	fseek(fp, offset, SEEK_CUR);		//����Ÿ �б� ���� ��ġ�� �̵�

	for (int k = 0; k < height; k++) {
		fread(&DDS->data[k * width * 4], lineSize, 1, fp);	//���Ͽ��� ������ �д´�.
		fseek(fp, lineGap, SEEK_CUR);						//���Ͽ��� �а� ���� ���� �ǳʶٰ�.. ���� ���� ��ġ�� �̵��Ѵ�.
	}

	/////���� �о�� �̹����� ũ���.. �̹��� ũ�⸦ ������/////
	DDS->header.dwHeight = height;
	DDS->header.dwWidth = width;

	/////���� �ݱ�/////
	fclose(fp);
	return DDS;
}