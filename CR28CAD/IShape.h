#pragma once
class IShape : public CObject
{
public:
  IShape();
  virtual ~IShape() = 0;

  virtual void OnDraw(CDC* pDC) = 0;
  virtual void OnDrawSelect(CDC* pDC) = 0;
  virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
  virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
  virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
  virtual void SetPenBrush(LOGPEN logpen, LOGBRUSH logbrush) = 0;
  virtual BOOL IsSelected(POINT pt) = 0;
  virtual void MoveShape(POINT ptMoveBegin, POINT ptEnd) = 0;
  virtual CPoint GetCenterPos() = 0;
  virtual float GetRotate() = 0;
  virtual void AddRotate(float rotate) = 0;
};

class IShapeFactory
{
public:
  virtual IShape* CreateShape() = 0;
};