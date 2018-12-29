package com.el.nv21;

public class NV21Utils {
    static {
        System.loadLibrary("el_nv21_utils");
    }
    public static void rotating(byte[] data,int w,int h,int rotating){
        if (data==null){
            throw new NullPointerException();
        }
        YUV420Rotating(data,w,h,rotating);
    }

    public static void crop(byte[] data,byte[] srcData,int w,int h,int left,int top,int right,int bottom){
        YUV420Crop(data,srcData,w,h,left,top,right,bottom);
    }

    public static void crop(byte[] data,byte[] srcData,int w,int h,int srcW,int srcH){
        int left=(w-srcW)/2;
        int top=(h-srcH)/2;
        int right=left;
        int bottom=top;
        if (0!=left%4){
            left=left-left%4;
            right=right+right%4;
        }
        if (0!=top%4){
            top=top-top%4;
            bottom=bottom+bottom%4;
        }

        YUV420Crop(data,srcData,w,h,left,top,right,bottom);
    }

    private native static void YUV420Rotating(byte[] imageData,int width,int height,int rotating);

    private native static void YUV420Crop(byte[] imageData,byte[] srcData,int width,int height,int left,int top,int right,int bottom);
}
