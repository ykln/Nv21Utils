#Nv21或Nv12的工具
* 旋转<br />
```
rotating(byte[] data,int w,int h,int rotating)
```
旋转会直接操作源数据
* 普通裁剪<br />
```data```目标数据<br />
```srcData```裁剪后生成的数据<br />
```w```目标数据的宽<br />
```h```目标数据的高<br />
```left```相对目标数据，生产数据的左边距<br />
```top```相对目标数据，生产数据的上边距<br />
```right```相对目标数据，生产数据的右边距<br />
```bottom```相对目标数据，生产数据的下边距<br />
```
crop(byte[] data,byte[] srcData,int w,int h,int left,int top,int right,int bottom)
```
* 居中裁剪<br />
```data```目标数据<br />
```srcData```裁剪后生成的数据<br />
```w```目标数据的宽<br />
```h```目标数据的高<br />
```srcW```目标数据的宽<br />
```srcH```目标数据的高<br />

```
crop(byte[] data,byte[] srcData,int w,int h,int srcW,int srcH)
```
