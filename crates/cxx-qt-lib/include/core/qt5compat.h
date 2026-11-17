// SPDX-License-Identifier: MIT OR Apache-2.0
//
// Definitions that let cxx-qt-lib build against Qt releases older than 5.15
// (Sailfish OS ships Qt 5.6).
#pragma once

#include <cstddef>

#include <QtCore/QByteArray>
#include <QtCore/QtGlobal>

#if (QT_VERSION < QT_VERSION_CHECK(5, 10, 0))
using qsizetype = QIntegerForSizeof<std::size_t>::Signed;
#endif

#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 0))
namespace Qt {
enum SplitBehaviorFlags
{
  KeepEmptyParts = 0,
  SkipEmptyParts = 0x1,
};
}
#endif

namespace rust {
namespace cxxqtlib1 {

#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
enum class QByteArrayBase64DecodingStatus
{
  Ok,
  IllegalInputLength,
  IllegalCharacter,
  IllegalPadding,
};

struct QByteArrayFromBase64Result
{
  QByteArray decoded;
  QByteArrayBase64DecodingStatus decodingStatus;
};
#else
using QByteArrayBase64DecodingStatus = QByteArray::Base64DecodingStatus;
using QByteArrayFromBase64Result = QByteArray::FromBase64Result;
#endif

// Qt < 5.15 does not declare QHash, QMap or the QJson types relocatable, even
// though they only hold d-pointers and can be moved with memcpy.
template<typename T>
constexpr bool isRelocatableOrOldQt =
  QT_VERSION < QT_VERSION_CHECK(5, 15, 0) || QTypeInfo<T>::isRelocatable;

} // namespace cxxqtlib1
} // namespace rust
