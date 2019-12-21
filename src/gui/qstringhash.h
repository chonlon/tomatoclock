#ifndef QSTRINGHASH_H
#define QSTRINGHASH_H

#include <QHash>
#include <QString>
#include <functional>

namespace std {
template <>
struct hash<QString> {
    std::size_t operator()(const QString& s) const {
        return qHash(s);
    }
};
}  // namespace std

#endif  // QSTRINGHASH_H
