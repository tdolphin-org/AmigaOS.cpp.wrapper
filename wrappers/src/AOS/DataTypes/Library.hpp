//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "AOS/Dos/LockScope.hpp"

#include "ValueTypes/GroupID.hpp"

#include <datatypes/datatypes.h>
#include <string>

namespace AOS::DataTypes
{
    class ObtainDataTypeResult
    {
        enum GroupID mGroupID;
        std::string mBaseName;

      public:
        ObtainDataTypeResult(const enum GroupID groupID = GroupID::None, const std::string &baseName = "");

        enum GroupID groupId() const
        {
            return mGroupID;
        }

        std::string baseName() const
        {
            return mBaseName;
        }

        /// @brief valid for empty or error
        bool isNone() const
        {
            return mGroupID == GroupID::None;
        }

        bool isSystem() const
        {
            return mGroupID == GroupID::System;
        }

        bool isText() const
        {
            return mGroupID == GroupID::Text;
        }

        bool isDocument() const
        {
            return mGroupID == GroupID::Document;
        }

        bool isSound() const
        {
            return mGroupID == GroupID::Sound;
        }

        bool isInstrument() const
        {
            return mGroupID == GroupID::Instrument;
        }

        bool isMusic() const
        {
            return mGroupID == GroupID::Music;
        }

        bool isPicture() const
        {
            return mGroupID == GroupID::Picture;
        }

        bool isAnimation() const
        {
            return mGroupID == GroupID::Animation;
        }

        bool isMovie() const
        {
            return mGroupID == GroupID::Movie;
        }
    };

    struct Library
    {
        /// @brief datatypes:ObtainDataType
        static ObtainDataTypeResult libObtainDataType(const AOS::Dos::LockScope &lockScope) noexcept;
        /// @brief datatypes:ObtainDataType
        static ObtainDataTypeResult libObtainDataType(const std::string &fileName) noexcept;
    };
}
