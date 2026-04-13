#pragma once

/**
 * shape.hpp — 図形クラス階層
 *
 * 実演する C++ クラス機能:
 *   - コンストラクタ / 仮想デストラクタ
 *   - 純粋仮想関数 (pure virtual) による抽象クラス
 *   - override / final キーワード
 *   - static メンバー変数 / 関数
 *   - const メンバー関数
 *   - operator<< オーバーロード
 */

#include <iostream>
#include <string>

// ─────────────────────────────────────────────
// Shape — 図形の抽象基底クラス
// ─────────────────────────────────────────────

class Shape {
public:
    /// 名前を受け取るコンストラクタ
    explicit Shape(std::string name);

    /// 仮想デストラクタ — 派生クラスのデストラクタを確実に呼ぶために virtual にする
    virtual ~Shape();

    // コピー / ムーブはデフォルト実装で OK（std::string が適切に管理してくれる）
    Shape(const Shape&)            = default;
    Shape& operator=(const Shape&) = default;
    Shape(Shape&&) noexcept        = default;
    Shape& operator=(Shape&&) noexcept = default;

    /// 面積を返す純粋仮想関数 — 派生クラスで必ず実装する
    virtual double area() const = 0;

    /// 周囲長を返す純粋仮想関数
    virtual double perimeter() const = 0;

    /// 説明文字列を返す仮想関数 — 派生クラスで上書き可能
    virtual std::string describe() const;

    /// 図形の名前を返す const メンバー関数 (noexcept)
    const std::string& name() const noexcept;

    /// これまでに生成された Shape 派生インスタンスの総数を返す static 関数
    static int instance_count() noexcept;

protected:
    /// 派生クラスから呼べるように protected で公開
    static void increment_count() noexcept;
    static void decrement_count() noexcept;

private:
    std::string name_;
    static int  instance_count_;  ///< 生存インスタンス数
};

/// ストリーム出力演算子 — describe() の内容を出力する
std::ostream& operator<<(std::ostream& os, const Shape& shape);

// ─────────────────────────────────────────────
// Circle — 円
// ─────────────────────────────────────────────

class Circle : public Shape {
public:
    /// 半径を受け取るコンストラクタ
    explicit Circle(double radius);

    double      area()      const override;
    double      perimeter() const override;
    std::string describe()  const override;

    double radius() const noexcept;

private:
    double radius_;
};

// ─────────────────────────────────────────────
// Rectangle — 長方形
// ─────────────────────────────────────────────

class Rectangle : public Shape {
public:
    /// 幅と高さを受け取るコンストラクタ
    Rectangle(double width, double height);

    double      area()      const override;
    double      perimeter() const override;
    std::string describe()  const override;

    double width()  const noexcept;
    double height() const noexcept;

private:
    double width_;
    double height_;
};
