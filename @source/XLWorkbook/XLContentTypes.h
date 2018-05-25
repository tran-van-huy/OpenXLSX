/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2018, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef OPENXL_XLCONTENTTYPES_H
#define OPENXL_XLCONTENTTYPES_H

#include "XLAbstractXMLFile.h"
#include "XLSpreadsheetElement.h"
#include "../@xml/xml.h"

#include <map>
#include <string>


namespace OpenXLSX
{
    class XLContentItem;

    using XLContentItemMap = std::map<std::string, std::unique_ptr<XLContentItem>>;

//======================================================================================================================
//========== XLColumnVector Enum =======================================================================================
//======================================================================================================================

    /**
     * @brief
     */
    enum class XLContentType
    {
        Workbook,
        WorkbookMacroEnabled,
        Worksheet,
        Chartsheet,
        ExternalLink,
        Theme,
        Styles,
        SharedStrings,
        Drawing,
        Chart,
        ChartStyle,
        ChartColorStyle,
        ControlProperties,
        CalculationChain,
        VBAProject,
        CoreProperties,
        ExtendedProperties,
        CustomProperties,
        Comments,
        Table,
        VMLDrawing,
        Unknown
    };

//======================================================================================================================
//========== XLContentItem Class =======================================================================================
//======================================================================================================================

    /**
     * @brief
     */
    class XLContentItem
    {
        friend class XLContentTypes;

//----------------------------------------------------------------------------------------------------------------------
//           Public Member Functions
//----------------------------------------------------------------------------------------------------------------------

    public:

        /**
         * @brief
         * @param other
         * @return
         */
        explicit XLContentItem(const XLContentItem &other);

        /**
         * @brief
         * @param other
         * @return
         */
        XLContentItem(XLContentItem &&other);

        /**
         * @brief
         * @param other
         * @return
         */
        XLContentItem &operator=(const XLContentItem &other);

        /**
         * @brief
         * @param other
         * @return
         */
        XLContentItem &operator=(XLContentItem &&other);

        /**
         * @brief
         * @return
         */
        XLContentType Type() const;

        /**
         * @brief
         * @return
         */
        const std::string &Path() const;

        /**
         * @brief
         */
        void DeleteItem();

//----------------------------------------------------------------------------------------------------------------------
//           Private Member Functions
//----------------------------------------------------------------------------------------------------------------------

    private:

        /**
         * @brief
         * @param node
         * @param path
         * @param type
         * @return
         */
        explicit XLContentItem(XMLNode node,
                               const std::string &path,
                               XLContentType type);

//----------------------------------------------------------------------------------------------------------------------
//           Public Member Variables
//----------------------------------------------------------------------------------------------------------------------

    private:

        XMLNode m_contentNode; /**< */
        std::string m_contentPath; /**< */
        XLContentType m_contentType; /**< */
    };


//======================================================================================================================
//========== XLContentTypes Class ==============================================================================
//======================================================================================================================

/**
 * @brief The purpose of this class is to load, store add and save item in the [Content_Types].xml file.
 */
    class XLContentTypes: public XLAbstractXMLFile,
                          public XLSpreadsheetElement
    {

//----------------------------------------------------------------------------------------------------------------------
//           Public Member Functions
//----------------------------------------------------------------------------------------------------------------------

    public:

        /**
         *
         * @param parent
         * @param filePath
         */
        explicit XLContentTypes(XLDocument &parent,
                                const std::string &filePath);

        /**
         * @brief Destructor
         */
        ~XLContentTypes() override = default;

        /**
         * @brief Add a new default key/value pair to the data store.
         * @param key The key
         * @param node The value
         */
        void AddDefault(const std::string &key,
                        XMLNode node);

        /**
         * @brief Add a new override key/value pair to the data store.
         * @param path The key
         * @param type The value
         */
        void addOverride(const std::string &path,
                         XLContentType type);

        /**
         * @brief Clear the overrides register.
         */
        void ClearOverrides();

        /**
         * @brief
         * @return
         */
        const XLContentItemMap *contentItems() const;

        /**
         * @brief
         * @param path
         * @return
         */
        XLContentItem *ContentItem(const std::string &path);

//----------------------------------------------------------------------------------------------------------------------
//           Protected Member Functions
//----------------------------------------------------------------------------------------------------------------------

    protected:

        /**
         * @brief
         * @return
         */
        bool ParseXMLData() override;

//----------------------------------------------------------------------------------------------------------------------
//           Private Member Variables
//----------------------------------------------------------------------------------------------------------------------

    private:
        std::map<std::string, XMLNode> m_defaults; /**< */
        XLContentItemMap m_overrides; /**< */
    };
}

#endif //OPENXL_XLCONTENTTYPES_H
