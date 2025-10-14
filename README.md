# Simple Ray Tracing

基本跟着 Ray Tracing in One Weekend 敲的，和 ShaderToy 的原理类似，主要为了加强 cpp 和光追细节。

## 效果



## 细节

- hittable 抽象类可以引申出组件的想法，定义物体的某种能力（可渲染、可移动、可被hit），接口多继承，引擎中的组件系统
- 利用光线和法线的方向一致性判断交点在内部还是外部（判断内外面），翻转 normal 对齐表面方向



