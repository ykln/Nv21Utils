#include <jni.h>
#include <string>
#include <android/log.h>



void NV21_rotate_to_90(jbyte *imageData, jint width, jint height);
void NV21_rotate_to_180(jbyte *imageData, jint width, jint height);
void NV21_rotate_to_270(jbyte *imageData, jint width, jint height);



extern "C"
JNIEXPORT void JNICALL
Java_com_el_nv21_NV21Utils_YUV420Rotating(JNIEnv *env, jobject instance, jbyteArray imageData_,
                                          jint width, jint height, jint rotating) {
    jbyte *imageData = env->GetByteArrayElements(imageData_, NULL);

    // TODO
    if (rotating%360==90){
        NV21_rotate_to_90(imageData,width,height);
    } else if (rotating%360==180){
        NV21_rotate_to_180(imageData,width,height);

    } else if (rotating%360==270){
        NV21_rotate_to_270(imageData,width,height);
    }

    env->ReleaseByteArrayElements(imageData_, imageData, 0);
}
void NV21_rotate_to_90(jbyte *imageData, jint width, jint height){

    jint y_size = width * height;
    jint buffser_size = y_size * 3 / 2;
    jbyte *nv21_rotated =new jbyte[buffser_size];
    // Rotate the Y luma

    for (int i = 0; i < buffser_size; ++i) {
        nv21_rotated[i]=imageData[i];
    }

    int i = 0;
    int startPos = (height - 1)*width;
    for (int x = 0; x < width; x++){
        int offset = startPos;
        for (int y = height - 1; y >= 0; y--)
        {
            imageData[i] = nv21_rotated[offset + x];
            i++;
            offset -= width;
        }
    }
    // Rotate the U and V color components
    i = buffser_size - 1;
    for (int x = width - 1; x > 0; x = x - 2){
        int offset = y_size;
        for (int y = 0; y < height / 2; y++)
        {
            imageData[i] = nv21_rotated[offset + x];
            i--;
            imageData[i] = nv21_rotated[offset + (x - 1)];
            i--;
            offset += width;
        }
    }
    delete nv21_rotated;
}


void NV21_rotate_to_180(jbyte *imageData, jint width, jint height) {
    jint y_size = width * height;
    jint buffser_size = y_size * 3 / 2;
    jbyte *yuv = new jbyte[buffser_size] ;

    for (int i = 0; i < buffser_size; ++i) {
        yuv[i]=imageData[i];
    }

    int i = 0;
    int count = 0;
    for (i = y_size - 1; i >= 0; i--) {
        imageData[count] = yuv[i];
        count++;
    }
    i = buffser_size - 1;
    for (i = buffser_size - 1; i >= y_size; i -= 2) {
        imageData[count++] = yuv[i - 1];
        imageData[count++] = yuv[i];
    }
    delete yuv;

}

void NV21_rotate_to_270(jbyte *imageData, jint width, jint height) {
    jint y_size = width * height;
    jint buffser_size = y_size * 3 / 2;
    jbyte *yuv = new jbyte[buffser_size] ;
    for (int i = 0; i < buffser_size; ++i) {
        yuv[i]=imageData[i];
    }

    int nWidth = 0, nHeight = 0;
    int wh = 0;
    int uvHeight = 0;
    if (width != nWidth || height != nHeight) {
        nWidth = width;
        nHeight = height;
        wh = width * height;
        uvHeight = height >> 1;// uvHeight = height / 2
    }

    int k = 0;
    for (int i = 0; i < width; i++) {
        int nPos = 0;
        for (int j = 0; j < height; j++) {
            imageData[k] = yuv[nPos + i];
            k++;
            nPos += width;
        }
    }
    for (int i = 0; i < width; i += 2) {
        int nPos = wh;
        for (int j = 0; j < uvHeight; j++) {
            imageData[k] = yuv[nPos + i];
            imageData[k + 1] = yuv[nPos + i + 1];
            k += 2;
            nPos += width;
        }
    }
//    NV21_rotate_to_90(imageData, width, height);
    NV21_rotate_to_180(imageData, width, height);
    delete yuv;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_el_nv21_NV21Utils_YUV420Crop(JNIEnv *env, jclass type, jbyteArray imageData_,
                                      jbyteArray srcData_, jint width, jint height, jint left,
                                      jint top, jint right, jint bottom) {
    jbyte *imageData = env->GetByteArrayElements(imageData_, NULL);
    jbyte *srcData = env->GetByteArrayElements(srcData_, NULL);

    // TODO
    jint newImageW=width-left-right;
    jint newImageH=height-top-bottom;
    jint newImagePixel=newImageW*newImageH;

    jint y_size = width * height;

    for (jint i = 0; i <newImageH; i++) {
        for (jint j = 0; j <newImageW;j++) {
            jint newDataIndex=i*newImageW+j;
            jint dataIndex=(top+i)*width+(left+j);
            srcData[newDataIndex]=imageData[dataIndex];
        }
    }

    jint newImageUVW=(newImageW>>1);
    jint newImageUVH=(newImageH>>1);
    jint uvW=(width>>1);
    jint uvLeft=left>>1;
    jint uvTop=top>>1;
    for (int i = 0; i <newImageUVH; i++) {
        for (jint j = 0; j <newImageUVW;j++) {
            jint newUVDataIndex=i*newImageUVW+j;
            jint uvDataIndex=(uvTop+i)*uvW+(uvLeft+j);
            newUVDataIndex=newUVDataIndex<<1;
            uvDataIndex=uvDataIndex<<1;
            srcData[newImagePixel+newUVDataIndex]=imageData[y_size+uvDataIndex];
            srcData[newImagePixel+newUVDataIndex+1]=imageData[y_size+uvDataIndex+1];
        }
    }


    env->ReleaseByteArrayElements(imageData_, imageData, 0);
    env->ReleaseByteArrayElements(srcData_, srcData, 0);
}