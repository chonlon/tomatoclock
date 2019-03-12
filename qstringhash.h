#ifndef QSTRINGHASH_H
#define QSTRINGHASH_H

#include <QString>
#include <QHash>
#include <functional>


namespace std {
  template<> struct hash<QString> {
    std::size_t operator()(const QString& s) const {
      return qHash(s);
    }
  };
}

#endif // QSTRINGHASH_H
