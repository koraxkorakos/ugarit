#pragma once
export module ugarit;

export import <concepts>;

export {

    namespace ugarit{

        using bits = std::uintmax_t;

        template <typename T>
        concept bladesig = requirs(T t) {
            { T::sig } -> std::same_as<bits>;
        };

        template <typename T> struct bb;

        template <typename T> struct bb;

    }
} // export